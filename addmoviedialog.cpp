#include "addmoviedialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

AddMovieDialog::AddMovieDialog(QWidget *parent) : QDialog(parent) {
    // Set up the form elements
    titleLineEdit = new QLineEdit(this);
    genreLineEdit = new QLineEdit(this);
    baseSKULineEdit = new QLineEdit(this);
    quantityLineEdit = new QLineEdit(this);
    addButton = new QPushButton(tr("Add Movie"), this);

    titleLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    genreLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    baseSKULineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    quantityLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    addButton->setStyleSheet("QPushButton {width: 150px; min-width: 150px; height: 30px; min-height: 30px; border-radius: 15px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 20px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");

    // Layout the form
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(new QLabel(tr("Title:")), titleLineEdit);
    formLayout->addRow(new QLabel(tr("Genre:")), genreLineEdit);
    formLayout->addRow(new QLabel(tr("Base SKU:")), baseSKULineEdit);
    formLayout->addRow(new QLabel(tr("Quantity:")), quantityLineEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(addButton);

    connect(addButton, &QPushButton::clicked, this, &AddMovieDialog::onAddButtonClicked);
}

QStringList AddMovieDialog::getMovieDetails() const {
    return movieDetails;
}

void AddMovieDialog::onAddButtonClicked() {
    // Validate the inputs
    bool ok;
    int quantity = quantityLineEdit->text().toInt(&ok);
    if (!ok || quantity <= 0) {
        QMessageBox::warning(this, tr("Input Error"), tr("Please enter a valid quantity."));
        return;
    }

    // Store the details and accept the dialog
    movieDetails << titleLineEdit->text()
                 << genreLineEdit->text()
                 << baseSKULineEdit->text()
                 << quantityLineEdit->text();
    accept();
}
