#ifndef INVENTORYMANAGEMENTDIALOG_H
#define INVENTORYMANAGEMENTDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include "addmoviedialog.h"
#include "editmoviedialog.h"

class InventoryManagementDialog : public QDialog {
    Q_OBJECT

public:
    explicit InventoryManagementDialog(QWidget *parent = nullptr);

private slots:
    void onAddMovieClicked();
    void onRemoveMovieClicked();
    void populateInventoryTable();
    void updateInventoryFile();

signals:
    void dataChanged();
private:
    QTableWidget *inventoryTable;
    QPushButton *addMovieButton;
    QPushButton *removeMovieButton;
    void loadInventoryFromFile();
    QString generateSerialNumber(const QString &baseSKU, int quantity);
    QString generateUniqueSKU();
};

#endif // INVENTORYMANAGEMENTDIALOG_H
