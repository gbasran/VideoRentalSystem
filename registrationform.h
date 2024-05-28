#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QVBoxLayout;
class QLabel;
QT_END_NAMESPACE

class RegistrationForm : public QDialog {
    Q_OBJECT

public:
    RegistrationForm(QWidget *parent = nullptr);

private slots:
    void onSaveClicked();

private:
    QLineEdit *firstNameLineEdit;
    QLineEdit *lastNameLineEdit;
    QLineEdit *phoneNumberLineEdit;
    QLineEdit *emailLineEdit;
    QLineEdit *addressLineEdit;
    QPushButton *saveButton;
    QVBoxLayout *layout;
};

#endif // REGISTRATIONFORM_H

