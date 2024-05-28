#include "returnvideodialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QPushButton>

ReturnVideoDialog::ReturnVideoDialog(QWidget *parent) : QDialog(parent) {
    model = new QStandardItemModel(this);
    tableView = new QTableView(this);
    searchLineEdit = new QLineEdit(this);
    searchButton = new QPushButton("Search", this);
    initializeUI();
    connectSignalsAndSlots();
    loadRentalsData();

    tableView->setStyleSheet("QTableWidget {font-family: Inter; font-size: 15px; font-weight: 500; line-height: normal;}");
    searchLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    searchButton->setStyleSheet("QPushButton {width: 150px; min-width: 150px; height: 30px; min-height: 30px; border-radius: 15px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 20px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");

}

void ReturnVideoDialog::initializeUI() {
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *searchLayout = new QHBoxLayout();

    searchLayout->addWidget(new QLabel("Search:"));
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(searchButton);

    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(tableView);

    setLayout(mainLayout);
    resize(800,600);
}

void ReturnVideoDialog::connectSignalsAndSlots() {
    connect(searchButton, &QPushButton::clicked, this, &ReturnVideoDialog::onSearchClicked);
    // Connect other signals and slots if necessary
}

void ReturnVideoDialog::loadRentalsData() {
    model->clear();
    model->setHorizontalHeaderLabels({"Rental ID", "Customer Name", "Movie ID", "Rental Date", "Return Date", "Status", "Action"});

    QFile file("rentals.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open rentals file.");
        return;
    }

    QTextStream in(&file);
    QString headerLine = in.readLine(); // Skip the header line
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        QList<QStandardItem *> items;
        for (const QString &field : fields) {
            items.append(new QStandardItem(field));
        }

        QPushButton *returnButton = new QPushButton("Return");
        returnButton->setStyleSheet("QPushButton {width: 90px; min-width: 90px; height: 25px; min-height: 25px; background: #296fa6; color: #F5F5F5; font-family: Inter; font-size: 20px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");

        connect(returnButton, &QPushButton::clicked, [this, line]() {
            this->onReturnClicked(line);
        });

        int row = model->rowCount();
        model->insertRow(row, items);
        tableView->setIndexWidget(model->index(row, 6), returnButton); // Assuming 6 is the "Action" column
    }
    file.close();
}

void ReturnVideoDialog::filterRentals(const QString &searchText) {
    for (int i = 0; i < model->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < model->columnCount() - 1; j++) { // Exclude the button column
            if (model->item(i, j)->text().contains(searchText, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        tableView->setRowHidden(i, !match);
    }
}

void ReturnVideoDialog::onSearchClicked() {
    filterRentals(searchLineEdit->text());
}

void ReturnVideoDialog::onReturnClicked(const QString &line) {
    QStringList fields = line.split(',');
    int statusIndex = 5; // Replace with the actual index of the Status field in your CSV

    // Check if the movie is already returned by checking the model, not the line itself
    int row = findRow(line);
    if (row != -1 && model->item(row, statusIndex)->text() == "Returned") {
        QMessageBox::information(this, "Info", "This movie is already returned.");
        return;
    }

    // Check is redundant here because we already checked the status above
    // fields[5] = "Returned"; // This line is not needed anymore, we'll update the model directly

    QString movieID = fields[2]; // Assuming the Movie ID is at index 2

    // Update the status in the model
    if (row != -1) {
        model->item(row, statusIndex)->setText("Returned");
        emit dataChanged();
    } else {
        // If for some reason the row was not found in the model, you should handle it here
        QMessageBox::critical(this, "Error", "The rental record could not be found in the table.");
        return;
    }

    // Update in file
    QFile file("rentals.csv");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open the rentals file for reading and writing.");
        return;
    }

    QString data = file.readAll();
    file.seek(0); // Go back to the start of the file
    file.resize(0); // Truncate the file

    // Replace the line with the updated status
    data.replace(line, model->item(row, 0)->text() + "," +
                        model->item(row, 1)->text() + "," +
                        model->item(row, 2)->text() + "," +
                        model->item(row, 3)->text() + "," +
                        model->item(row, 4)->text() + "," +
                        "Returned");
    emit dataChanged();

    QTextStream out(&file);
    out << data;
    file.close();

    // Update inventory after the rental status update is successful
    updateInventory(movieID); // Call updateInventory to update the quantity in inventory
    emit dataChanged();
}


int ReturnVideoDialog::findRow(const QString &line) {
    // Iterate over the rows to find which one matches the line
    for (int i = 0; i < model->rowCount(); i++) {
        QStringList rowValues;
        for (int j = 0; j < model->columnCount() - 1; j++) { // Exclude the button column
            rowValues << model->item(i, j)->text();
        }
        if (rowValues.join(',') == line) {
            return i;
        }
    }
    return -1; // Not found
}

void ReturnVideoDialog::updateInventory(const QString &movieID) {
    QFile file("inventory.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Failed to open the inventory file for reading.");
        return;
    }

    QString data;
    QTextStream in(&file);
    bool found = false;
    QString line;
    QStringList details;
    while (!in.atEnd()) {
        line = in.readLine();
        if (line.startsWith(movieID + ",")) {
            details = line.split(',');
            details[3] = QString::number(details[3].toInt() + 1); // Increase the quantity by 1
            if(details[3].toInt() > 0) details[4] = "Available"; // Set status to Available if quantity > 0
            line = details.join(',');
            found = true;
        }
        data += line + "\n";
    }
    file.close();

    if (found) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Error", "Failed to open the inventory file for writing.");
            return;
        }
        QTextStream out(&file);
        out << data;
        file.close();
    } else {
        QMessageBox::warning(this, "Warning", "Movie ID not found in inventory.");
    }
}
