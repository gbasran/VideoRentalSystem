#ifndef ADDMOVIEDIALOG_H
#define ADDMOVIEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>

class AddMovieDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddMovieDialog(QWidget *parent = nullptr);
    QStringList getMovieDetails() const;

private slots:
    void onAddButtonClicked();

private:
    QLineEdit *titleLineEdit;
    QLineEdit *genreLineEdit;
    QLineEdit *baseSKULineEdit;
    QLineEdit *quantityLineEdit;
    QPushButton *addButton;
    QStringList movieDetails;
};

#endif // ADDMOVIEDIALOG_H
