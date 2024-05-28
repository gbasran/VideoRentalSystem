#include "usermanagementdialog.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QHeaderView>

UserManagementDialog::UserManagementDialog(QWidget *parent) : QDialog(parent) {
    layout = new QVBoxLayout(this);

    QLabel *searchLabel = new QLabel("Search Name:");
    searchNameLineEdit = new QLineEdit();
    searchNameButton = new QPushButton("Search");
    registerNewUserButton = new QPushButton("Register New User");
    editButton = new QPushButton("Edit", this);

    searchLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    searchNameLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    searchNameButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    registerNewUserButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    searchLabel->setStyleSheet("QLabel {width: 300px; height: 90px; color: #1C0F13; font-family: Inter; font-size: 18px; font-style: normal; font-weight: 600; line-height: normal;}");
    searchNameButton->setStyleSheet("QPushButton {width: 150px; min-width: 150px; height: 30px; min-height: 30px; border-radius: 15px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 20px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");
    registerNewUserButton->setStyleSheet("QPushButton {width: 200px; min-width: 200px; height: 30px; min-height: 30px; border-radius: 15px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 20px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");
    editButton->setStyleSheet("QPushButton {width: 150px; min-width: 150px; height: 30px; min-height: 30px; border-radius: 15px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 20px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");
    searchNameLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");

    // Use a horizontal layout for the search section
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchNameLineEdit);
    searchLayout->addWidget(searchNameButton);

    // Add the search layout to the main vertical layout
    layout->addWidget(searchLabel);
    layout->addLayout(searchLayout);
    layout->addWidget(registerNewUserButton);

    searchResultsTable = new QTableWidget(this);
    searchResultsTable->setColumnCount(5); // Adjust based on your CSV structure
    searchResultsTable->setHorizontalHeaderLabels({"First Name", "Last Name", "Phone Number", "Email", "Address"});
    searchResultsTable->horizontalHeader()->setStretchLastSection(true);
    searchResultsTable->setStyleSheet("QTableWidget {font-family: Inter; font-size: 15px; font-weight: 500; line-height: normal;}");
    searchResultsTable->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color: #81B2D9;font-family: Inter; font-size: 15px; font-weight: 500; line-height: normal;}");

    connect(editButton, &QPushButton::clicked, this, &UserManagementDialog::onEditButtonClicked);

    populateTableWithUsers();

    layout->addWidget(searchResultsTable);
    layout->addWidget(editButton);

    // Connect signals to slots
    connect(registerNewUserButton, &QPushButton::clicked, this, &UserManagementDialog::onRegisterNewUserClicked);
    connect(searchNameButton, &QPushButton::clicked, this, &UserManagementDialog::onSearchNameClicked);
    this->setMinimumSize(800,600);
}

void UserManagementDialog::onRegisterNewUserClicked() {
    RegistrationForm registrationForm(this);
    if (registrationForm.exec() == QDialog::Accepted) {
        populateTableWithUsers();  // Refresh the table to show the new user
    }
}

void UserManagementDialog::onSearchNameClicked() {
    QString searchText = searchNameLineEdit->text().trimmed();

    if (searchText.isEmpty()) {
        QMessageBox::information(this, "Search", "Please enter a search term.");
        return;
    }

    QString filePath = "users.csv";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open file: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine(); // Read the header line

    searchResultsTable->setRowCount(0); // Clear previous search results

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList userData = line.split(',');

        for (const QString &data : userData) {
            if (data.compare(searchText, Qt::CaseInsensitive) == 0) {
                int currentRow = searchResultsTable->rowCount();
                searchResultsTable->insertRow(currentRow);

                for (int i = 0; i < userData.size(); i++) {
                    QTableWidgetItem *item = new QTableWidgetItem(userData.at(i));
                    searchResultsTable->setItem(currentRow, i, item);
                }
                break; // Found a match, move to next line
            }
        }
    }

    file.close();
}

void UserManagementDialog::onEditButtonClicked() {
    int selectedRow = searchResultsTable->currentRow();
    if (selectedRow == -1) {
        QMessageBox::warning(this, "Warning", "Please select a record to edit.");
        return;
    }

    EditUserDialog editDialog(this);
    QStringList userData;
    for (int i = 0; i < searchResultsTable->columnCount(); ++i) {
        userData << searchResultsTable->item(selectedRow, i)->text();
    }

    editDialog.setData(userData);

    if (editDialog.exec() == QDialog::Accepted) {
        QStringList newData = editDialog.getData();
        for (int i = 0; i < newData.size(); ++i) {
            searchResultsTable->item(selectedRow, i)->setText(newData.at(i));
        }

        updateCsvFile(); // This function needs to be implemented to update the CSV file
        populateTableWithUsers();
    }
}

void UserManagementDialog::updateCsvFile() {
    QFile file("users.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open file for writing.");
        return;
    }

    QTextStream out(&file);
    out << "First Name,Last Name,Phone Number,Email,Address\n"; // Writing headers

    for (int i = 0; i < searchResultsTable->rowCount(); ++i) {
        QStringList rowContents;
        for (int j = 0; j < searchResultsTable->columnCount(); ++j) {
            rowContents << searchResultsTable->item(i, j)->text();
        }
        out << rowContents.join(',') << "\n";
    }

    file.close();
}
void UserManagementDialog::populateTableWithUsers() {
    QString filePath = "users.csv";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open file: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine(); // Read and discard the header line

    searchResultsTable->setRowCount(0); // Clear the table

    while (!in.atEnd()) {
        line = in.readLine();
        QStringList userData = line.split(',');
        int currentRow = searchResultsTable->rowCount();
        searchResultsTable->insertRow(currentRow);

        for (int i = 0; i < userData.size(); ++i) {
            QTableWidgetItem *item = new QTableWidgetItem(userData.at(i));
            searchResultsTable->setItem(currentRow, i, item);
        }
    }

    file.close();
}



