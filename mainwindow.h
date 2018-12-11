#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "adminlogin.h"
#include "canvas.h"
#include "contact.h"

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

    Qt::AlignmentFlag getAlign();

    Qt::GlobalColor getTextColor();

    QFont::Weight getTextWeight();

    QFont::Style getTextStyle();

    QString getFontFamily();

private slots:
    void on_actionLogin_triggered();//Shows admin login

    void on_actionQuit_triggered();//Quits program

    void on_actionEnable_Disable_Privledges_triggered(); //Emable privledges

    void on_pushButton_clicked(); //Add shape

    void on_pushButton_deleteShape_clicked(); //Show delete shapes

    void on_pushButton_move_clicked(); //Show move shapes

    void on_actionContact_Info_triggered(); //Show contact info

    void on_pushButton_2_clicked(); //Refreshes shapeTables

private:
    Ui::MainWindow *ui;
    AdminLogin *uiLogin;
    bool adminPrivW{false};
    Contact *uiContact;

};

#endif // MAINWINDOW_H
