#include "addrentaldialog.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStandardItem>
#include <QDateTime>

AddRentalDialog::AddRentalDialog(QWidget *parent)
    : QDialog(parent),
      customerSearchResultsModel(new QStringListModel(this)),
      movieSearchResultsModel(new QStringListModel(this)) {

    customerSearchLineEdit = new QLineEdit(this);
    movieSearchLineEdit = new QLineEdit(this);
    customerSearchResultsListView = new QListView(this);
    movieSearchResultsListView = new QListView(this);
    rentalDateEdit = new QDateEdit(QDate::currentDate(), this);
    returnDateEdit = new QDateEdit(QDate::currentDate().addDays(7), this); // Default rental period of 7 days
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    customerSearchLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    movieSearchLineEdit->setStyleSheet("QLineEdit {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    customerSearchResultsListView->setStyleSheet("QListView {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");
    movieSearchResultsListView->setStyleSheet("QListView {border-width: 5px; border-radius: 8px; border-color: #81B2D9;}");


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(tr("Customer Search:"), customerSearchLineEdit);
    formLayout->addRow(tr("Customer Results:"), customerSearchResultsListView);
    formLayout->addRow(tr("Movie Search:"), movieSearchLineEdit);
    formLayout->addRow(tr("Movie Results:"), movieSearchResultsListView);
    formLayout->addRow(tr("Rental Date:"), rentalDateEdit);
    formLayout->addRow(tr("Return Date:"), returnDateEdit);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    customerSearchResultsListView->setModel(customerSearchResultsModel);
    movieSearchResultsListView->setModel(movieSearchResultsModel);

    connect(customerSearchLineEdit, &QLineEdit::textChanged, this, &AddRentalDialog::updateCustomerSearchResults);
    connect(movieSearchLineEdit, &QLineEdit::textChanged, this, &AddRentalDialog::updateMovieSearchResults);
    connect(customerSearchResultsListView, &QListView::clicked, this, &AddRentalDialog::customerSelected);
    connect(movieSearchResultsListView, &QListView::clicked, this, &AddRentalDialog::movieSelected);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AddRentalDialog::onAddClicked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AddRentalDialog::reject);

    loadCustomersFromFile();
    loadMoviesFromFile();

    setLayout(mainLayout);
}

AddRentalDialog::~AddRentalDialog() {
}

void AddRentalDialog::onAddClicked() {
    if (selectedCustomerName.isEmpty() || selectedMovieName.isEmpty()) {  // Changed from selectedMovieSKU to selectedMovieName
        QMessageBox::warning(this, tr("Input Error"), tr("Please select a customer and a movie."));
        return;
    }

    // Call updateInventory here with the movie name
    updateInventory(selectedMovieName, -1); // Assuming decrement by 1 for rental

    // Now append the rental to rentals.csv
    appendRentalToCsv(selectedCustomerName, selectedMovieName, rentalDateEdit->date(), returnDateEdit->date());  // Change to pass name instead of SKU

    accept(); // Close the dialog
}


void AddRentalDialog::updateCustomerSearchResults(const QString &text) {
    customerSearchResultsModel->setStringList(getCustomerSearchResults(text));
}

void AddRentalDialog::updateMovieSearchResults(const QString &text) {
    movieSearchResultsModel->setStringList(getMovieSearchResults(text));
}


QStringList AddRentalDialog::getCustomerSearchResults(const QString &searchText) {
    QStringList results;
    for (const QString &customer : customers) {
        if (customer.contains(searchText, Qt::CaseInsensitive)) {
            results.append(customer);
        }
    }
    return results;
}

QStringList AddRentalDialog::getMovieSearchResults(const QString &searchText) {
    QStringList results;
    for (const QString &movie : movies) {
        // Adjust condition to search within movie names
        if (movie.contains(searchText, Qt::CaseInsensitive)) {
            results.append(movie);
        }
    }
    return results;
}


void AddRentalDialog::customerSelected(const QModelIndex &index) {
    selectedCustomerName = index.data(Qt::DisplayRole).toString();
}

void AddRentalDialog::movieSelected(const QModelIndex &index) {
    selectedMovieName = index.data(Qt::DisplayRole).toString();
}

void AddRentalDialog::loadCustomersFromFile() {
    QFile file("users.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not open users.csv");
        return;
    }

    QTextStream in(&file);
    in.readLine(); // Skip the header line

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() > 0)
            customers.append(fields.at(0)); // Assuming the name is in the first column
    }

    file.close();
}
void AddRentalDialog::loadMoviesFromFile() {
    QFile file("inventory.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not open inventory.csv");
        return;
    }

    QTextStream in(&file);
    in.readLine(); // Skip the header line

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        // Assuming the name is the first column (index 0)
        if (fields.size() > 1)
            movies.append(fields.at(0)); // Adjust the index as needed
    }

    file.close();
}

void AddRentalDialog::appendRentalToCsv(const QString &customerName, const QString &movieName, const QDate &rentalDate, const QDate &returnDate) {
    QFile file("rentals.csv");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not open rentals.csv");
        return;
    }

    QTextStream out(&file);
    // Generate a unique rental ID, you can use QDateTime for simplicity
    QString rentalID = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    out << rentalID << ","
        << customerName << ","
        << movieName << ","
        << rentalDate.toString("yyyy-MM-dd") << ","
        << returnDate.toString("yyyy-MM-dd") << ","
        << "Rented" << "\n";

    file.close();
}
void AddRentalDialog::updateInventory(const QString &movieName, int quantityChange) {
    QFile file("inventory.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not open inventory.csv");
        return;
    }

    QString data;
    QTextStream in(&file);
    QStringList lines = in.readAll().split("\n");
    file.close();

    bool inventoryUpdated = false;
    for (int i = 1; i < lines.size(); ++i) { // Skip header line
        QString line = lines.at(i);
        QStringList fields = line.split(',');
        if (!fields.isEmpty() && fields.at(0) == movieName) { // Assuming movie name is in the first column
            int currentQuantity = fields.at(3).toInt(); // Assuming quantity is in the fourth column
            int newQuantity = currentQuantity + quantityChange;
            fields[3] = QString::number(qMax(0, newQuantity)); // Prevent negative quantity

            // Update the Rental Status based on the new quantity
            if (newQuantity <= 0) {
                fields[4] = "Unavailable"; // Assuming rental status is in the fifth column
            } else {
                fields[4] = "Available"; // Or any other logic you have to set availability
            }

            lines[i] = fields.join(',');
            inventoryUpdated = true;
            break; // Assuming unique movie names, so stop after finding the movie
        }
    }

    if (inventoryUpdated) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Error", "Could not write to inventory.csv");
            return;
        }

        QTextStream out(&file);
        // Write the header back first
        out << lines.first() << "\n"; // Assuming the first line is the header
        // Then write the updated inventory data
        for (int i = 1; i < lines.size(); ++i) {
            out << lines[i] << "\n";
        }
        file.close();
    } else {
        QMessageBox::information(this, "Not Found", "Movie not found in inventory.");
    }
}


