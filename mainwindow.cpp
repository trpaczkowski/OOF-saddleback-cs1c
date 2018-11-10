#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Tab_Modify->setEnabled(false);
    ui->Tab_Shape->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLogin_triggered()
{
    uiLogin = new AdminLogin(this);
    uiLogin->show();
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

//Will set admin privledges
void MainWindow::SetAdminPriv(bool adminIn)
{
    adminPrivW = adminIn;
}

void MainWindow::on_actionEnable_Disable_Privledges_triggered()
{
    //Gets new admin privledges
    SetAdminPriv(uiLogin->GetAdminPriv());

    ui->Tab_Modify->setEnabled(adminPrivW);
    ui->Tab_Shape->setEnabled(adminPrivW);

    if( ui->Tab_Modify->isEnabled())
    {
        QMessageBox::information(this, "Admin Actions", "Admin actions enabled. Check the \"Modify Tab\" for actions.");
        ui->label_userType->setText("Admin user");
    }
    else
    {
        QMessageBox::critical(this, "Admin Actions", "Not allowed to enable! Must login to admin.");
    }

}
