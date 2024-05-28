#include "customerselectiondialog.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

CustomerSelectionDialog::CustomerSelectionDialog(QWidget *parent) : QDialog(parent) {
    searchLineEdit = new QLineEdit(this);
    searchButton = new QPushButton(tr("Search"), this);
    selectUserButton = new QPushButton(tr("Select User"), this);
    usersTable = new QTableWidget(this);
    usersTable->setColumnCount(5); // Match the number of columns to your CSV file
    usersTable->setHorizontalHeaderLabels({"First Name", "Last Name", "Phone Number", "Email", "Address"});
    usersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    usersTable->setSelectionMode(QAbstractItemView::SingleSelection);
    usersTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(searchLineEdit);
    layout->addWidget(searchButton);
    layout->addWidget(usersTable);
    layout->addWidget(selectUserButton);

    connect(searchButton, &QPushButton::clicked, this, &CustomerSelectionDialog::onSearchClicked);
    connect(selectUserButton, &QPushButton::clicked, this, &CustomerSelectionDialog::onSelectUserClicked);
    resize(800,600);


    populateTableWithUsers();
}

void CustomerSelectionDialog::populateTableWithUsers() {
    QFile file("users.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Could not open users.csv file.");
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine(); // Skip header line
    while (!in.atEnd()) {
        line = in.readLine();
        QStringList userData = line.split(',');
        int currentRow = usersTable->rowCount();
        usersTable->insertRow(currentRow);
        for (int i = 0; i < userData.size(); i++) {
            usersTable->setItem(currentRow, i, new QTableWidgetItem(userData.at(i)));
        }
    }

    file.close();
}

void CustomerSelectionDialog::onSearchClicked() {
    QString searchText = searchLineEdit->text().trimmed();
    searchUsers(searchText);
}

void CustomerSelectionDialog::searchUsers(const QString &text) {
    // Iterate over all rows and hide those that do not match the search query
    for (int i = 0; i < usersTable->rowCount(); ++i) {
        bool match = false; // A flag to indicate if any of the columns contain the search text
        for (int j = 0; j < usersTable->columnCount(); ++j) {
            QTableWidgetItem *item = usersTable->item(i, j);
            if (item->text().contains(text, Qt::CaseInsensitive)) {
                match = true;
                break; // If we find a match, no need to check further; move to the next row
            }
        }
        usersTable->setRowHidden(i, !match); // Hide the row if there is no match
    }
}

void CustomerSelectionDialog::onSelectUserClicked() {
    int selectedRow = usersTable->currentRow();
    if (selectedRow == -1) {
        QMessageBox::warning(this, "Warning", "Please select a user first.");
        return;
    }

    QStringList userData;
    for (int col = 0; col < usersTable->columnCount(); col++) {
        userData << usersTable->item(selectedRow, col)->text();
    }

    // Now create and show the CustomerDetailsDialog with the selected user's data
    CustomerDetailsDialog detailsDialog(userData, this);
    detailsDialog.exec();  // Show the dialog as a modal window
}

QStringList CustomerSelectionDialog::getSelectedUserData() const {
    int selectedRow = usersTable->currentRow();
    QStringList userData;
    if (selectedRow != -1) {
        for (int col = 0; col < usersTable->columnCount(); col++) {
            QTableWidgetItem *item = usersTable->item(selectedRow, col);
            if (item) {
                userData << item->text();
            } else {
                userData << "";
            }
        }
    }
    return userData;
}
