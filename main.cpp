#include "src/mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFontDatabase::addApplicationFont(":/fonts/volume1/venus_uprising.otf");
    MainWindow w;
    w.show();
    return a.exec();
}
