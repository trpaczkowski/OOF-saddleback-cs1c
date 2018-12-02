#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "adminlogin.h"
#include "canvas.h"
<<<<<<< HEAD
#include "contactwindow.h"
#include <QMessageBox>
=======
>>>>>>> f10f7fc401ffd2c2bc22c0dc688ad62b4db56600

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void SetAdminPriv(bool adminIn); //changes admin priv
    ~MainWindow();

    //Pen properties
    Qt::GlobalColor getPenColor();

    int getPenWidth();

    Qt::PenStyle getPenStyle();

    Qt::PenCapStyle getPenCapStyle();

    Qt::PenJoinStyle getPenJoinStyle();

    Qt::GlobalColor getBrushColor();

    Qt::BrushStyle getBrushStyle();

private slots:
    void on_actionLogin_triggered();

    void on_actionQuit_triggered();

    void on_actionEnable_Disable_Privledges_triggered();

    void on_pushButton_clicked();

<<<<<<< HEAD
    void on_actionhi_triggered();

=======
>>>>>>> f10f7fc401ffd2c2bc22c0dc688ad62b4db56600
private:
    Ui::MainWindow *ui;
    AdminLogin *uiLogin;
    bool adminPrivW{false};
<<<<<<< HEAD
    Canvas *canvasUi;
    contactwindow *uiContact;
=======
    Canvas canvasUi;
>>>>>>> f10f7fc401ffd2c2bc22c0dc688ad62b4db56600

};

#endif // MAINWINDOW_H
