#include "mainwindow.h"
#include <QApplication>

//TAYLOR PACZKOWSKI reporting on OOF
//OSCAR LOPEZ reporting on OOF
//ISAAC ESTRADA reported on OOF
//TRAVIS NGUYEN reporting in OOF

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
