#include "editmoviedialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

EditMovieDialog::EditMovieDialog(QWidget *parent) : QDialog(parent) {
    // Create and position the form elements
    titleLineEdit = new QLineEdit(this);
    genreLineEdit = new QLineEdit(this);
    baseSKULineEdit = new QLineEdit(this);
    quantityLineEdit = new QLineEdit(this);
    saveChangesButton = new QPushButton(tr("Save Changes"), this);

    // Set up the form layout
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(new QLabel(tr("Title:")), titleLineEdit);
    formLayout->addRow(new QLabel(tr("Genre:")), genreLineEdit);
    formLayout->addRow(new QLabel(tr("Base SKU:")), baseSKULineEdit);
    formLayout->addRow(new QLabel(tr("Quantity:")), quantityLineEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(saveChangesButton);

    // Connect the Save Changes button to the appropriate slot
    connect(saveChangesButton, &QPushButton::clicked, this, &EditMovieDialog::onSaveChangesClicked);
}


void EditMovieDialog::setMovieDetails(const QStringList &details) {
    // Ensure the number of details matches the expected number (now 5, including rental status)
    if (details.size() == 5) {
        titleLineEdit->setText(details.at(0));
        genreLineEdit->setText(details.at(1));
        baseSKULineEdit->setText(details.at(2));
        quantityLineEdit->setText(details.at(3));
        rentalStatusLineEdit->setText(details.at(4)); // Set the rental status
    } else {
        QMessageBox::critical(this, "Error", "Incorrect number of details provided.");
    }
}





QStringList EditMovieDialog::getMovieDetails() const {
    return movieDetails;
}

void EditMovieDialog::onSaveChangesClicked() {
    // Validate the inputs as in AddMovieDialog
    bool ok;
    int quantity = quantityLineEdit->text().toInt(&ok);
    if (!ok || quantity <= 0) {
        QMessageBox::warning(this, tr("Input Error"), tr("Please enter a valid quantity."));
        return;
    }

    // Update the details and close the dialog
    movieDetails[0] = titleLineEdit->text();
    movieDetails[1] = genreLineEdit->text();
    movieDetails[2] = baseSKULineEdit->text();
    movieDetails[3] = quantityLineEdit->text();
    accept();
}
