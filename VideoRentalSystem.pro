QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    VideoRentalSystem.cpp \
    addmoviedialog.cpp \
    addrentaldialog.cpp \
    edituserdialog.cpp \
    inventorymanagementdialog.cpp \
    main.cpp \
    registrationform.cpp \
    rentalmanagementdialog.cpp \
    returnvideodialog.cpp \
    usermanagementdialog.cpp

HEADERS += \
    VideoRentalSystem.h \
    addmoviedialog.h \
    addrentaldialog.h \
    edituserdialog.h \
    inventorymanagementdialog.h \
    registrationform.h \
    rentalmanagementdialog.h \
    returnvideodialog.h \
    usermanagementdialog.h

FORMS += \
    VideoRentalSystem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
