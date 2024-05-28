#ifndef RETURNVIDEODIALOG_H
#define RETURNVIDEODIALOG_H

#include <QDialog>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

class ReturnVideoDialog : public QDialog {
    Q_OBJECT

public:
    explicit ReturnVideoDialog(QWidget *parent = nullptr);
    void loadRentalsData();
    void filterRentals(const QString &searchText);

private slots:
    void onSearchClicked();
    void onReturnClicked(const QString &line);

signals:
    void dataChanged();

private:
    QTableView *tableView;             // Table to display the rentals
    QLineEdit *searchLineEdit;         // Input for filtering/searching the rentals
    QPushButton *searchButton;         // Button to trigger the search/filter action
    QStandardItemModel *model;         // Model to handle the data of the rentals

    void initializeUI();               // Method to initialize the user interface
    void connectSignalsAndSlots();     // Method to connect signals and slots
    int findRow(const QString &line);  // Helper method to find a row based on a line from the CSV
    void updateInventory(const QString &movieID);
};

#endif // RETURNVIDEODIALOG_H
