#include "edituserdialog.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QMessageBox>

EditUserDialog::EditUserDialog(QWidget *parent) : QDialog(parent) {
    QFormLayout *formLayout = new QFormLayout();

    firstNameLineEdit = new QLineEdit(this);
    lastNameLineEdit = new QLineEdit(this);
    phoneNumberLineEdit = new QLineEdit(this);
    emailLineEdit = new QLineEdit(this);
    addressLineEdit = new QLineEdit(this);
    saveButton = new QPushButton(tr("Save"), this);

    firstNameLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    lastNameLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    phoneNumberLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    emailLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    addressLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    saveButton->setStyleSheet("QPushButton {width: 150px; min-width: 150px; height: 30px; min-height: 30px; border-radius: 15px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 20px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");


    formLayout->addRow(tr("First Name:"), firstNameLineEdit);
    formLayout->addRow(tr("Last Name:"), lastNameLineEdit);
    formLayout->addRow(tr("Phone Number:"), phoneNumberLineEdit);
    formLayout->addRow(tr("Email:"), emailLineEdit);
    formLayout->addRow(tr("Address:"), addressLineEdit);

    connect(saveButton, &QPushButton::clicked, this, &EditUserDialog::onSaveClicked);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(saveButton);
}

void EditUserDialog::setData(const QStringList &data) {
    if (data.size() != 5) {
        QMessageBox::critical(this, tr("Error"), tr("Invalid data provided to the dialog."));
        return;
    }

    firstNameLineEdit->setText(data.at(0));
    lastNameLineEdit->setText(data.at(1));
    phoneNumberLineEdit->setText(data.at(2));
    emailLineEdit->setText(data.at(3));
    addressLineEdit->setText(data.at(4));
}

QStringList EditUserDialog::getData() const {
    return QStringList() << firstNameLineEdit->text()
                         << lastNameLineEdit->text()
                         << phoneNumberLineEdit->text()
                         << emailLineEdit->text()
                         << addressLineEdit->text();
}

void EditUserDialog::onSaveClicked() {
    // Validation or further processing can be added here
    accept(); // This will close the dialog
}
