#ifndef CUSTOMERDETAILSDIALOG_H
#define CUSTOMERDETAILSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QStringList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

class CustomerDetailsDialog : public QDialog {
    Q_OBJECT

public:
    explicit CustomerDetailsDialog(const QStringList &userData, QWidget *parent = nullptr);

private slots:
    void onAddRentalClicked();
    void onManageRentalsClicked();

private:
    QLabel *nameLabel;
    QLabel *phoneLabel;
    QLabel *emailLabel;
    QLabel *addressLabel;
    QPushButton *addRentalButton;
    QPushButton *manageRentalsButton;

    void setupUI(const QStringList &userData);
};

#endif // CUSTOMERDETAILSDIALOG_H
