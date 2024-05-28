#include "VideoRentalSystem.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include <QFile>
#include <QApplication>
#include <QDebug>

VideoRentalSystem::VideoRentalSystem(QWidget *parent) : QMainWindow(parent) {
    // Initialize the main widget and layout
    QWidget *mainWidget = new QWidget(this);
    layout = new QVBoxLayout(mainWidget);
    initializeRentalsFile();

    // Create labels and buttons
    title = new QLabel("Rent-A-Video");
    returnNum = new QLabel("53");
    upcomingReturnsLabel = new QLabel("Upcoming returns");
    inventoryNum = new QLabel("66");
    videosInventoryLabel = new QLabel("Videos in inventory");
    rentVideoButton = new QPushButton("Rent Video");
    returnVideoButton = new QPushButton("Rental Return");
    manageUsersButton = new QPushButton("Manage Users");
    manageInventoryButton = new QPushButton("Manage Inventory");



    rentVideoButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    returnVideoButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    manageUsersButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    manageInventoryButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    title->setStyleSheet("QLabel {width: 596px; height: 90px; color: #1C0F13; font-family: Garamond; font-size: 80px; font-style: normal; font-weight: 600; line-height: normal;}");
    returnNum->setStyleSheet("QLabel {width: 596px; height: 90px; color: #14293E; font-family: Inter; font-size: 180px; font-style: normal; font-weight: 600; line-height: normal;}");
    upcomingReturnsLabel->setStyleSheet("QLabel {width: 596px; height: 90px; color: #14293E; font-family: Inter; font-size: 65px; font-style: normal; font-weight: 600; line-height: normal;}");
    inventoryNum->setStyleSheet("QLabel {width: 596px; height: 90px; color: #14293E; font-family: Inter; font-size: 180px; font-style: normal; font-weight: 600; line-height: normal;}");
    videosInventoryLabel->setStyleSheet("QLabel {width: 596px; height: 90px; color: #14293E; font-family: Inter; font-size: 65px; font-style: normal; font-weight: 600; line-height: normal;}");
    rentVideoButton->setStyleSheet("QPushButton {width: 550px; min-width: 550px; height: 115px; min-height: 115px; border-radius: 57px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 55px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");
    returnVideoButton->setStyleSheet("QPushButton {width: 550px; min-width: 550px; height: 115px; min-height: 115px; border-radius: 57px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 55px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");
    manageUsersButton->setStyleSheet("QPushButton {width: 550px; min-width: 550px; height: 115px; min-height: 115px; border-radius: 57px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 55px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");
    manageInventoryButton->setStyleSheet("QPushButton {width: 550px; min-width: 550px; height: 115px; min-height: 115px; border-radius: 57px; background: #81B2D9; color: #F5F5F5; font-family: Inter; font-size: 55px; font-style: normal; font-weight: 600; line-height: normal;}""QPushButton:hover {background: #629FD0;}");

    // Create layouts for buttons
    QHBoxLayout *leftButtonLayout = new QHBoxLayout;
    QHBoxLayout *rightButtonLayout = new QHBoxLayout;
    QHBoxLayout *topButtonLayout = new QHBoxLayout;
    //QHBoxLayout *titleLayout = new QHBoxLayout;

    // Add buttons to layouts
    leftButtonLayout->addWidget(rentVideoButton);
    leftButtonLayout->addWidget(manageUsersButton);
    rightButtonLayout->addWidget(returnVideoButton);
    rightButtonLayout->addWidget(manageInventoryButton);

    // Create and add spacers for top layout
    QSpacerItem *spacerLeft = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *spacerRight = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    topButtonLayout->addItem(spacerLeft);
    topButtonLayout->addItem(spacerRight);
    topButtonLayout->setContentsMargins(0, 0, 0, 0);

    // Add layouts to main layout
  //  layout->setSpacing(15);
    layout->addWidget(title);
    layout->addWidget(returnNum);
    layout->addWidget(upcomingReturnsLabel);
    layout->addWidget(inventoryNum);
    layout->addWidget(videosInventoryLabel);
    layout->addLayout(topButtonLayout);
    layout->addLayout(leftButtonLayout);
    layout->addLayout(rightButtonLayout);

    // Set the main widget and layout
    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    // Set the window title and size
    setWindowTitle("Rent-A-Video");
    resize(1920, 1080);
    setStyleSheet("QMainWindow { background-color: #E2E2E2; }");
    connect(manageInventoryButton, &QPushButton::clicked, this, &VideoRentalSystem::onManageInventoryClicked);

    // Connect signals and slots
    connect(rentVideoButton, &QPushButton::clicked, this, &VideoRentalSystem::onRentVideoClicked);
    connect(returnVideoButton, &QPushButton::clicked, this, &VideoRentalSystem::onReturnVideoClicked);
    connect(manageUsersButton, &QPushButton::clicked, this, &VideoRentalSystem::onManageUsersClicked);
    connect(manageInventoryButton, &QPushButton::clicked, this, &VideoRentalSystem::onManageInventoryClicked);
    userManagementDialog = nullptr;

}

void VideoRentalSystem::onRentVideoClicked() {
    RentalManagementDialog *rentalDialog = new RentalManagementDialog(this);
    connect(rentalDialog, &RentalManagementDialog::dataChanged, this, &VideoRentalSystem::updateDataDisplay);
    rentalDialog->setAttribute(Qt::WA_DeleteOnClose);
    rentalDialog->show();
}



void VideoRentalSystem::onReturnVideoClicked() {
    ReturnVideoDialog *dialog = new ReturnVideoDialog(this);
    connect(dialog, &ReturnVideoDialog::dataChanged, this, &VideoRentalSystem::updateDataDisplay);
    dialog->setAttribute(Qt::WA_DeleteOnClose);  // Ensure dialog is deleted after closing
    dialog->show();
}



void VideoRentalSystem::onManageUsersClicked() {
    if (userManagementDialog == nullptr) {
        userManagementDialog = new UserManagementDialog(this);
        userManagementDialog->setAttribute(Qt::WA_DeleteOnClose);
        // Connect the finished signal to a new slot to handle dialog closure
        connect(userManagementDialog, &UserManagementDialog::finished,
                this, &VideoRentalSystem::onUserManagementDialogClosed);
    }

    userManagementDialog->show();
    userManagementDialog->raise();
    userManagementDialog->activateWindow();
}

void VideoRentalSystem::onUserManagementDialogClosed() {
    userManagementDialog = nullptr;  // Reset the pointer to avoid dangling reference
}

void VideoRentalSystem::onManageInventoryClicked() {
    static InventoryManagementDialog *inventoryDialog = nullptr;

    if (!inventoryDialog) {
        inventoryDialog = new InventoryManagementDialog(this);
        inventoryDialog->setAttribute(Qt::WA_DeleteOnClose);

        // Ensure this connection is made
        connect(inventoryDialog, &InventoryManagementDialog::dataChanged, this, &VideoRentalSystem::updateDataDisplay);

        connect(inventoryDialog, &QObject::destroyed, []() {
            inventoryDialog = nullptr;
        });

        inventoryDialog->show();
    } else {
        inventoryDialog->raise();
        inventoryDialog->activateWindow();
    }
}


void VideoRentalSystem::initializeRentalsFile() {
    QString rentalsFilePath = "rentals.csv";
    QFile rentalsFile(rentalsFilePath);

    // Check if the file already exists
    if (!rentalsFile.exists()) {
        // If not, create the file and add a header
        if (!rentalsFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Error", "Unable to create the rentals file: " + rentalsFile.errorString());
            return;
        }

        QTextStream out(&rentalsFile);
        out << "Rental ID,Customer ID,Movie ID,Rental Date,Return Date,Status\n"; // Example header
        rentalsFile.close();
    }
}
int VideoRentalSystem::calculateUpcomingReturns() {
    int upcomingReturns = 0;
    QFile rentalFile("rentals.csv");
    if (rentalFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&rentalFile);
        QString line = in.readLine(); // Skip the header line

        while (!in.atEnd()) {
            line = in.readLine();
            QStringList fields = line.split(',');
            // Check if we have enough fields to access index 5
            if (fields.size() > 5 && fields[5] != "Returned") {
                upcomingReturns++;
            }
        }
        rentalFile.close();
    } else {
        QMessageBox::warning(this, "Warning", "Cannot open rentals file.");
    }
    return upcomingReturns;
}

int VideoRentalSystem::calculateInventoryTotal() {
    int inventoryTotal = 0;
    QFile inventoryFile("inventory.csv");
    if (inventoryFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&inventoryFile);
        QString line = in.readLine(); // Skip the header line

        while (!in.atEnd()) {
            line = in.readLine();
            QStringList fields = line.split(',');
            // Check if we have enough fields to access index 3
            if (fields.size() > 3) {
                inventoryTotal += fields[3].toInt(); // Assuming that the quantity is at index 3
            }
        }
        inventoryFile.close();
    } else {
        QMessageBox::warning(this, "Warning", "Cannot open inventory file.");
    }
    return inventoryTotal;
}

void VideoRentalSystem::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);

    // Update the labels with the latest data
    returnNum->setText(QString::number(calculateUpcomingReturns()));
    inventoryNum->setText(QString::number(calculateInventoryTotal()));
}

void VideoRentalSystem::updateDataDisplay() {
    returnNum->setText(QString::number(calculateUpcomingReturns()));
    inventoryNum->setText(QString::number(calculateInventoryTotal()));
}




