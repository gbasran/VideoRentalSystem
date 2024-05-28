#ifndef EDITMOVIEDIALOG_H
#define EDITMOVIEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>

class EditMovieDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditMovieDialog(QWidget *parent = nullptr);
    void setMovieDetails(const QStringList &details);
    QStringList getMovieDetails() const;

private slots:
    void onSaveChangesClicked();

private:
    QLineEdit *titleLineEdit;
    QLineEdit *genreLineEdit;
    QLineEdit *baseSKULineEdit;
    QLineEdit *quantityLineEdit;
    QLineEdit *rentalStatusLineEdit;
    QPushButton *saveChangesButton;
    QStringList movieDetails;
};

#endif // EDITMOVIEDIALOG_H
