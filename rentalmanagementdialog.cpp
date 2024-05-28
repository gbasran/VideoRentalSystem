#include "rentalmanagementdialog.h"
#include "addrentaldialog.h"
#include <QMessageBox>
#include <QHeaderView>

RentalManagementDialog::RentalManagementDialog(QWidget *parent) : QDialog(parent), model(new QStandardItemModel(this)) {

    QLabel *searchLabel = new QLabel("Search by name:");
    rentalsView = new QTableView(this);
    searchLineEdit = new QLineEdit(this);
    searchButton = new QPushButton("Search", this);
    addRentalButton = new QPushButton("Add Rental", this);


    searchLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    searchLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    searchButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    addRentalButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


    searchLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    searchButton->setStyleSheet("QPushButton {width: 150px; min-width: 150px; height: 30px; min-height: 30px; border-radius: 15px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 20px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");
    addRentalButton->setStyleSheet("QPushButton {width: 175px; min-width: 175px; height: 30px; min-height: 30px; border-radius: 15px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 20px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");
    rentalsView->setStyleSheet("QTableWidget {font-family: Inter; font-size: 15px; font-weight: 500; line-height: normal;}");
    rentalsView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color: #81B2D9;font-family: Inter; font-size: 15px; font-weight: 500; line-height: normal;}");


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(searchButton);

    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(rentalsView);
    mainLayout->addWidget(addRentalButton);


    setLayout(mainLayout);

    connect(searchButton, &QPushButton::clicked, this, &RentalManagementDialog::onSearchClicked);
    connect(addRentalButton, &QPushButton::clicked, this, &RentalManagementDialog::onAddRentalClicked);

    resize(800,600);

    loadRentalsData();
}

void RentalManagementDialog::loadRentalsData() {
    model->clear();
    model->setHorizontalHeaderLabels({"Rental ID", "Customer Name", "Movie ID", "Rental Date", "Return Date", "Status"});

    QFile file("rentals.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open rentals file.");
        return;
    }

    QTextStream in(&file);
    QString headerLine = in.readLine(); // Read the header line but do not process it
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QStandardItem *> standardItemsList;
        for (const QString &field : line.split(',')) {
            standardItemsList.append(new QStandardItem(field));
        }
        model->appendRow(standardItemsList);
    }

    file.close();

    rentalsView->setModel(model);
    rentalsView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void RentalManagementDialog::onSearchClicked() {
    filterRentals(searchLineEdit->text());
}

void RentalManagementDialog::filterRentals(const QString &searchText) {
    for (int i = 0; i < model->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < model->columnCount(); ++j) {
            if (model->item(i, j)->text().contains(searchText, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        rentalsView->setRowHidden(i, !match);
    }
}

void RentalManagementDialog::onAddRentalClicked() {
    AddRentalDialog addRentalDialog(this);

    // Execute the dialog and check if it was accepted
    if (addRentalDialog.exec() == QDialog::Accepted) {
        // If the rental was successfully added, update the rentals table
        // You might need to adjust this based on how you're managing data
        loadRentalsData();  // Reload or update the data in the rentals table
        emit dataChanged();
    }
}


