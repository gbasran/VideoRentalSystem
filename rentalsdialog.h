#ifndef RENTALSDIALOG_H
#define RENTALSDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>

class RentalsDialog : public QDialog {
    Q_OBJECT

public:
    explicit RentalsDialog(QWidget *parent = nullptr);
    void populateRentalsTable();

private slots:
    void onManageRentalsClicked(int row);

private:
    QTableWidget *rentalsTable;
    void addManageButtons();
};

#endif // RENTALSDIALOG_H
