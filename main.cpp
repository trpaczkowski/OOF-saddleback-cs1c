#include "mainwindow.h"
#include <QApplication>

//TAYLOR PACZKOWSKI reporting on OOF
//OSCAR LOPEZ reporting on OOF

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}