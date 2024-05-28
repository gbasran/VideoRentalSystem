#ifndef EDITUSERDIALOG_H
#define EDITUSERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>

class EditUserDialog : public QDialog {
    Q_OBJECT

public:
    EditUserDialog(QWidget *parent = nullptr);
    void setData(const QStringList &data);
    QStringList getData() const;

private slots:
    void onSaveClicked();

private:
    QLineEdit *firstNameLineEdit;
    QLineEdit *lastNameLineEdit;
    QLineEdit *phoneNumberLineEdit;
    QLineEdit *emailLineEdit;
    QLineEdit *addressLineEdit;
    QPushButton *saveButton;
};

#endif // EDITUSERDIALOG_H
