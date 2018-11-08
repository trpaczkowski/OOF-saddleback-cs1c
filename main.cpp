#include "mainwindow.h"
#include <QApplication>

//TAYLOR PACZKOWSKI
//Oscar

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
