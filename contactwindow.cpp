#include "contactwindow.h"
#include "ui_contactwindow.h"

contactwindow::contactwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::contactwindow)
{
    ui->setupUi(this);
}

contactwindow::~contactwindow()
{
    delete ui;
}
