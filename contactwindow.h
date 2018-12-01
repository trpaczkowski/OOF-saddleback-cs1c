#ifndef CONTACTWINDOW_H
#define CONTACTWINDOW_H

#include <QDialog>

namespace Ui {
class contactwindow;
}

class contactwindow : public QDialog
{
    Q_OBJECT

public:
    explicit contactwindow(QWidget *parent = 0);
    ~contactwindow();

private:
    Ui::contactwindow *ui;
    contactwindow *uiContact;
};

#endif // CONTACTWINDOW_H
