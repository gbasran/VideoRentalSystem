#ifndef USERMANAGEMENTDIALOG_H
#define USERMANAGEMENTDIALOG_H

#include <QDialog>
#include "registrationform.h"
#include <QTableWidget>
#include "edituserdialog.h"
QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QVBoxLayout;
class QLabel;
QT_END_NAMESPACE

class UserManagementDialog : public QDialog {
    Q_OBJECT

public:
    UserManagementDialog(QWidget *parent = nullptr);

private slots:
    void onRegisterNewUserClicked();
    void onSearchNameClicked(); // New slot for searching names
    void onEditButtonClicked();
    void updateCsvFile();

private:
    QLineEdit *searchNameLineEdit;
    QPushButton *registerNewUserButton;
    QPushButton *searchNameButton; // Button to search for the name
    QPushButton *editButton;       // Button to edit the selected record
    QTableWidget *searchResultsTable; // Table to display search results
    QVBoxLayout *layout;
    void populateTableWithUsers();
};

#endif // USERMANAGEMENTDIALOG_H
