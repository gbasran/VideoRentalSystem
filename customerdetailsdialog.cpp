#include "customerdetailsdialog.h"

CustomerDetailsDialog::CustomerDetailsDialog(const QStringList &userData, QWidget *parent)
    : QDialog(parent) {
    setupUI(userData);
}

void CustomerDetailsDialog::setupUI(const QStringList &userData) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Assuming userData contains [First Name, Last Name, Phone, Email, Address]
    nameLabel = new QLabel("Name: " + userData.at(0) + " " + userData.at(1), this);
    phoneLabel = new QLabel("Phone: " + userData.at(2), this);
    emailLabel = new QLabel("Email: " + userData.at(3), this);
    addressLabel = new QLabel("Address: " + userData.at(4), this);

    addRentalButton = new QPushButton("Add Rental", this);
    manageRentalsButton = new QPushButton("Manage Rentals", this);

    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(phoneLabel);
    mainLayout->addWidget(emailLabel);
    mainLayout->addWidget(addressLabel);
    mainLayout->addWidget(addRentalButton);
    mainLayout->addWidget(manageRentalsButton);

    connect(addRentalButton, &QPushButton::clicked, this, &CustomerDetailsDialog::onAddRentalClicked);
    connect(manageRentalsButton, &QPushButton::clicked, this, &CustomerDetailsDialog::onManageRentalsClicked);
}

void CustomerDetailsDialog::onAddRentalClicked() {
    // Implement the logic to add a rental for the user
    // This might open another dialog or perform some actions directly
    QMessageBox::information(this, "Action", "Add rental functionality not implemented.");
}

void CustomerDetailsDialog::onManageRentalsClicked() {
    // Implement the logic to manage rentals for the user
    // This might open another dialog showing the user's current rentals, allowing modifications
    QMessageBox::information(this, "Action", "Manage rentals functionality not implemented.");
}
