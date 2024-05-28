#include "registrationform.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>

RegistrationForm::RegistrationForm(QWidget *parent) : QDialog(parent) {
    layout = new QVBoxLayout(this);

    // Create form fields
    firstNameLineEdit = new QLineEdit();
    lastNameLineEdit = new QLineEdit();
    phoneNumberLineEdit = new QLineEdit();
    emailLineEdit = new QLineEdit();
    addressLineEdit = new QLineEdit();
    saveButton = new QPushButton("Save");
    QLabel *fNameLabel = new QLabel("First name:");
    QLabel *lNameLabel = new QLabel("Last name:");
    QLabel *phoneNumLabel = new QLabel("Phone number:");
    QLabel *emailLabel = new QLabel("Email:");
    QLabel *addressLabel = new QLabel("Address:");

    firstNameLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    lastNameLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    phoneNumberLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    emailLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    addressLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    saveButton->setStyleSheet("QPushButton {width: 150px; min-width: 150px; height: 30px; min-height: 30px; border-radius: 15px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 20px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");
    fNameLabel->setStyleSheet("QLabel {width: 300px; height: 90px; color: #1C0F13; font-family: Inter; font-size: 18px; font-style: normal; font-weight: 500; line-height: normal;}");
    lNameLabel->setStyleSheet("QLabel {width: 300px; height: 90px; color: #1C0F13; font-family: Inter; font-size: 18px; font-style: normal; font-weight: 500; line-height: normal;}");
    phoneNumLabel->setStyleSheet("QLabel {width: 300px; height: 90px; color: #1C0F13; font-family: Inter; font-size: 18px; font-style: normal; font-weight: 500; line-height: normal;}");
    emailLabel->setStyleSheet("QLabel {width: 300px; height: 90px; color: #1C0F13; font-family: Inter; font-size: 18px; font-style: normal; font-weight: 500; line-height: normal;}");
    addressLabel->setStyleSheet("QLabel {width: 300px; height: 90px; color: #1C0F13; font-family: Inter; font-size: 18px; font-style: normal; font-weight: 500; line-height: normal;}");

    // Add widgets to the layout
    layout->addWidget(fNameLabel);
    layout->addWidget(firstNameLineEdit);
    layout->addWidget(lNameLabel);
    layout->addWidget(lastNameLineEdit);
    layout->addWidget(phoneNumLabel);
    layout->addWidget(phoneNumberLineEdit);
    layout->addWidget(emailLabel);
    layout->addWidget(emailLineEdit);
    layout->addWidget(addressLabel);
    layout->addWidget(addressLineEdit);
    layout->addWidget(saveButton);

    // Connect the save button signal to the onSaveClicked slot
    connect(saveButton, &QPushButton::clicked, this, &RegistrationForm::onSaveClicked);
}

void RegistrationForm::onSaveClicked() {
    QString filePath = "users.csv"; // Using a relative path for simplicity

    QFile file(filePath);

    // Check if the file already exists to decide whether we need to write a header
    bool fileExists = file.exists();

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open file: " + file.errorString());
        return;
    }

    QTextStream out(&file);

    // If the file didn't exist, we write the header
    if (!fileExists) {
        out << "First Name,Last Name,Phone Number,Email,Address\n";
    }

    // Write data to file
    out << firstNameLineEdit->text().trimmed() << ","
        << lastNameLineEdit->text().trimmed() << ","
        << phoneNumberLineEdit->text().trimmed() << ","
        << emailLineEdit->text().trimmed() << ","
        << addressLineEdit->text().trimmed() << "\n";

    // Flush the stream to ensure all data is written to the file
    out.flush();
    file.close();

    QMessageBox::information(this, "Success", "User registered successfully.");
    this->accept(); // Close the dialog
}



