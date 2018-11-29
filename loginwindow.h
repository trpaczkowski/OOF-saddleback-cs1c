#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "window.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;
class QMainWindow;
QT_END_NAMESPACE

//! [0]
class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    LoginWindow();

private slots:
    void openMainWindow();

private:
    QLabel* login;
    QLineEdit* username;
    QLineEdit* password;
    QPushButton* submit;
    QPushButton* guestLogin;
    Window* window;
    QString admin_username;
    QString admin_password;

};
//! [0]
#endif // LOGINWINDOW_H
