#ifndef VIDEORENTALSYSTEM_H
#define VIDEORENTALSYSTEM_H

#include <QMainWindow>
#include "usermanagementdialog.h"
#include "inventorymanagementdialog.h"
#include "rentalmanagementdialog.h"
#include "returnvideodialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QVBoxLayout;
class QWidget;
QT_END_NAMESPACE

class VideoRentalSystem : public QMainWindow {
    Q_OBJECT

public:
    VideoRentalSystem(QWidget *parent = nullptr);

private slots:
    void onRentVideoClicked();
    void onReturnVideoClicked();
    void onManageUsersClicked();
    void onManageInventoryClicked();
    void onUserManagementDialogClosed();
    void updateDataDisplay();

private:
    QLabel *title;
    QLabel *returnNum;
    QLabel *inventoryNum;
    QLabel *upcomingReturnsLabel;
    QLabel *videosInventoryLabel;
    QPushButton *rentVideoButton;
    QPushButton *returnVideoButton;
    QPushButton *manageUsersButton;
    QPushButton *manageInventoryButton;
    QVBoxLayout *layout;
    UserManagementDialog *userManagementDialog;
    void initializeRentalsFile();
    int calculateUpcomingReturns();
    int calculateInventoryTotal();
    void showEvent(QShowEvent *event);
    InventoryManagementDialog *inventoryDialog;

};

#endif // VIDEORENTALSYSTEM_H
