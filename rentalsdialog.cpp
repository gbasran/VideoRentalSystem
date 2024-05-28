#include "rentalsdialog.h"
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPushButton>

RentalsDialog::RentalsDialog(QWidget *parent) : QDialog(parent) {
    rentalsTable = new QTableWidget(this);
    rentalsTable->setColumnCount(/* set the number of columns based on your CSV structure plus one for the button */);
    rentalsTable->setHorizontalHeaderLabels(/* set your column headers here, plus an extra header for the Manage button */);
    rentalsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    rentalsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    rentalsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(rentalsTable);

    populateRentalsTable();
}

void RentalsDialog::populateRentalsTable() {
    QFile file("rentals.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Could not open rentals.csv file.");
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine(); // Assuming the first line is headers
    while (!in.atEnd()) {
        line = in.readLine();
        QStringList rentalDetails = line.split(',');
        int currentRow = rentalsTable->rowCount();
        rentalsTable->insertRow(currentRow);
        for (int i = 0; i < rentalDetails.size(); ++i) {
            rentalsTable->setItem(currentRow, i, new QTableWidgetItem(rentalDetails.at(i)));
        }

        QPushButton *manageButton = new QPushButton("Manage Rentals", this);
        connect(manageButton, &QPushButton::clicked, [this, currentRow]() { onManageRentalsClicked(currentRow); });
        rentalsTable->setCellWidget(currentRow, rentalDetails.size(), manageButton);
    }
    file.close();
}

void RentalsDialog::onManageRentalsClicked(int row) {
    // Implement the logic for managing the rental corresponding to the clicked row
    QMessageBox::information(this, "Info", "Manage Rentals button clicked for row: " + QString::number(row));
    // Here you can open another dialog or perform other actions to manage the selected rental
}
