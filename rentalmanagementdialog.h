#ifndef RENTALMANAGEMENTDIALOG_H
#define RENTALMANAGEMENTDIALOG_H

#include <QDialog>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>

class RentalManagementDialog : public QDialog {
    Q_OBJECT

public:
    explicit RentalManagementDialog(QWidget *parent = nullptr);
    void loadRentalsData();

private slots:
    void onSearchClicked();
    void onAddRentalClicked();
signals:
    void dataChanged();
private:
    QTableView *rentalsView;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QPushButton *addRentalButton;
    QStandardItemModel *model;
    void filterRentals(const QString &searchText);
    void refreshRentalData();
};

#endif // RENTALMANAGEMENTDIALOG_H
