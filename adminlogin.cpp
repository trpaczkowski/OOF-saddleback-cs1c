#include "adminlogin.h"
#include "ui_adminlogin.h"
#include <QMessageBox>
AdminLogin::AdminLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
}

AdminLogin::~AdminLogin()
{
    delete ui;
}

void AdminLogin::on_buttonBox_accepted()
{
    QString username = ui->lineEdit_user->text();
    QString password = ui->lineEdit_pass->text();
    if(username == "admin" && password == "pass000")
    {
        QMessageBox::information(this, "Admin Login", "Administrator priviledges added");
        adminPrivA = true;
    }
    else
    {
        QMessageBox::information(this, "Admin Login", "Wrong password and/or username.");
    }
}

void AdminLogin::on_buttonBox_rejected()
{
    QMessageBox::information(this, "Admin Login", "End");
}

bool AdminLogin::GetAdminPriv()
{
    return adminPrivA;
}
