#include "VideoRentalSystem.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoRentalSystem w;
    w.show();
    return a.exec();
}
