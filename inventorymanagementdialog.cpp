#include "inventorymanagementdialog.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

InventoryManagementDialog::InventoryManagementDialog(QWidget *parent)
    : QDialog(parent), inventoryTable(new QTableWidget(this)),
      addMovieButton(new QPushButton(tr("Add Movie"), this)),
      removeMovieButton(new QPushButton(tr("Remove Movie"), this)){
    removeMovieButton->setStyleSheet("QPushButton {width: 150px; min-width: 150px; height: 30px; min-height: 30px; border-radius: 15px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 20px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");
    addMovieButton->setStyleSheet("QPushButton {width: 150px; min-width: 150px; height: 30px; min-height: 30px; border-radius: 15px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 20px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");


    // Setup the table with 5 columns
    inventoryTable->setColumnCount(5);
    inventoryTable->setHorizontalHeaderLabels({"Title", "Genre", "Serial Number", "Quantity", "Rental Status"});
    inventoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    inventoryTable->setStyleSheet("QTableWidget {font-family: Inter; font-size: 15px; font-weight: 500; line-height: normal;}");
    inventoryTable->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color: #81B2D9;font-family: Inter; font-size: 15px; font-weight: 500; line-height: normal;}");


    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(inventoryTable);
    layout->addWidget(addMovieButton);
    layout->addWidget(removeMovieButton);
    resize(800,600);

    connect(addMovieButton, &QPushButton::clicked, this, &InventoryManagementDialog::onAddMovieClicked);
    connect(removeMovieButton, &QPushButton::clicked, this, &InventoryManagementDialog::onRemoveMovieClicked);

    populateInventoryTable();
}

void InventoryManagementDialog::populateInventoryTable() {
    loadInventoryFromFile();
}

void InventoryManagementDialog::loadInventoryFromFile() {
    QString filePath = "inventory.csv";
    QFile file(filePath);

    // Create file with headers if it doesn't exist
    if (!file.exists()) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Error", "Unable to create the file: " + file.errorString());
            return;
        }
        QTextStream out(&file);
        out << "Title,Genre,Serial Number,Quantity,Rental Status\n";
        file.close();
    }

    // Load the inventory from file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the file: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine(); // Skip header line
    inventoryTable->setRowCount(0); // Clear the table

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList itemDetails = line.split(',');
        if (itemDetails.size() != 5) continue; // Ensure there are exactly 5 elements

        int currentRow = inventoryTable->rowCount();
        inventoryTable->insertRow(currentRow);
        for (int i = 0; i < itemDetails.size(); i++) {
            inventoryTable->setItem(currentRow, i, new QTableWidgetItem(itemDetails.at(i)));
        }
    }

    file.close();
}

void InventoryManagementDialog::updateInventoryFile() {
    QString filePath = "inventory.csv";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the file for writing: " + file.errorString());
        return;
    }

    QTextStream out(&file);
    // Write the header
    out << "Title,Genre,Serial Number,Quantity,Rental Status\n";
    for (int row = 0; row < inventoryTable->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < inventoryTable->columnCount(); ++col) {
            QTableWidgetItem *item = inventoryTable->item(row, col);
            rowData << item->text();
        }
        out << rowData.join(',') << "\n";
    }
    file.close();
}

void InventoryManagementDialog::onAddMovieClicked() {
    // Assuming you have a dialog to enter the details for a new movie
    AddMovieDialog addDialog(this);
    if (addDialog.exec() == QDialog::Accepted) {
        QStringList movieDetails = addDialog.getMovieDetails();  // Get the details from the dialog
        if (movieDetails.size() != 4) return; // Should not include the serial number

        int currentRow = inventoryTable->rowCount();
        inventoryTable->insertRow(currentRow);

        // Generate a base SKU if not provided, for example using a timestamp or UUID
        QString baseSKU = !movieDetails.at(2).isEmpty() ? movieDetails.at(2) : generateUniqueSKU();

        // Insert items into the table
        for (int i = 0; i < movieDetails.size(); ++i) {
            inventoryTable->setItem(currentRow, i, new QTableWidgetItem(movieDetails.at(i)));
        }

        // Generate serial numbers based on the quantity
        QString quantityStr = movieDetails.at(3);
        int quantity = quantityStr.toInt();
        for (int i = 1; i <= quantity; ++i) {
            QString serialNumber = generateSerialNumber(baseSKU, i);
            // Add logic to handle individual serial numbers, if necessary
        }

        // Add the rental status as "Available" by default
        inventoryTable->setItem(currentRow, 4, new QTableWidgetItem("Available"));

        // Update the .csv file
        updateInventoryFile();
        emit dataChanged();
    }
}

// Slot to remove a selected movie
void InventoryManagementDialog::onRemoveMovieClicked() {
    int currentRow = inventoryTable->currentRow();
    if (currentRow != -1) {
        inventoryTable->removeRow(currentRow);
        updateInventoryFile(); // Save changes to the .csv
        emit dataChanged();
    } else {
        QMessageBox::warning(this, "Warning", "Please select a movie to remove.");
    }
}


QString InventoryManagementDialog::generateSerialNumber(const QString &baseSKU, int copyNumber) {
    return QString("%1-%2").arg(baseSKU, QString::number(copyNumber).rightJustified(2, '0'));
}

QString InventoryManagementDialog::generateUniqueSKU() {
    // Implement a method to generate a unique SKU, e.g., based on the current timestamp
    // This is a placeholder function
    return QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
}

