#ifndef ADDRENTALDIALOG_H
#define ADDRENTALDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QListView>
#include <QStringListModel>
#include <QDateEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QDialogButtonBox>

class AddRentalDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddRentalDialog(QWidget *parent = nullptr);
    ~AddRentalDialog();

private slots:
    void onAddClicked();
    void updateCustomerSearchResults(const QString &text);
    void updateMovieSearchResults(const QString &text);
    void customerSelected(const QModelIndex &index);
    void movieSelected(const QModelIndex &index);

private:
    QLineEdit *customerSearchLineEdit;
    QLineEdit *movieSearchLineEdit;
    QListView *customerSearchResultsListView;
    QListView *movieSearchResultsListView;
    QStringListModel *customerSearchResultsModel;
    QStringListModel *movieSearchResultsModel;
    QDateEdit *rentalDateEdit;
    QDateEdit *returnDateEdit;
    QPushButton *addButton;
    QDialogButtonBox *buttonBox;

    QString selectedCustomerName;
    QString selectedMovieName;

    QStringList getCustomerSearchResults(const QString &searchText);
    QStringList getMovieSearchResults(const QString &searchText);
    void appendRentalToCsv(const QString &customerName, const QString &movieSKU, const QDate &rentalDate, const QDate &returnDate);
    void loadCustomersFromFile();
    void loadMoviesFromFile();
    void updateInventory(const QString &movieName, int quantity);
    QStringList customers;
    QStringList movies;
};

#endif // ADDRENTALDIALOG_H
