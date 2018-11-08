#include "mainwindow.h"
#include <QApplication>

//TAYLOR PACZKOWSKI

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
