#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "adminlogin.h"
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

private slots:
    void on_actionLogin_triggered();

    void on_actionQuit_triggered();

    void on_actionEnable_Disable_Privledges_triggered();

private:
    Ui::MainWindow *ui;
    AdminLogin *uiLogin;
    bool adminPrivW{false};
};

#endif // MAINWINDOW_H
