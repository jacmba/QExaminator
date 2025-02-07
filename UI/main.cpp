#include "mainwindow.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon logo(":/images/logo_transparent.png");
    a.setWindowIcon(logo);
    MainWindow w;
    w.show();
    return a.exec();
}
