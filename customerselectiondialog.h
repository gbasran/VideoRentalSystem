#ifndef CUSTOMERSELECTIONDIALOG_H
#define CUSTOMERSELECTIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include "customerdetailsdialog.h"
class CustomerSelectionDialog : public QDialog {
    Q_OBJECT

public:
    explicit CustomerSelectionDialog(QWidget *parent = nullptr);
    QStringList getSelectedUserData() const;

private slots:
    void onSearchClicked();
    void onSelectUserClicked();
    void populateTableWithUsers();


private:
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QPushButton *selectUserButton;
    QTableWidget *usersTable;

    void searchUsers(const QString &text);
};

#endif // CUSTOMERSELECTIONDIALOG_H
