#include "loginwindow.h"
#include <QtWidgets>

LoginWindow::LoginWindow()
{
    setWindowTitle("2D Graphics");
    admin_password = "kaththelegend";
    admin_username = "admin";

    login = new QLabel("Welcome to the OOF 2D Graphics Simulator!");
    username = new QLineEdit();
    //username->setFocus();
    username->setPlaceholderText("Username");
    password = new QLineEdit();
    password->setEchoMode(QLineEdit::Password);
    password->setPlaceholderText("Password");
    connect(password, SIGNAL(returnPressed()), this, SLOT(openMainWindow()));
    submit = new QPushButton("Log in");
    guestLogin = new QPushButton("Log in as "
                                 "a guest");
    connect(submit, SIGNAL(clicked(bool)), this, SLOT(openMainWindow()));
    connect(guestLogin, SIGNAL(clicked(bool)), this, SLOT(openMainWindow()));
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(login);
    mainLayout->addWidget(username);
    mainLayout->addWidget(password);
    mainLayout->addWidget(submit);
    mainLayout->addWidget(guestLogin);

    setLayout(mainLayout);
}

void LoginWindow::openMainWindow()
{
    if (QObject::sender() == submit || QObject::sender() == password || QObject::sender() == username)
    {
        if (username->text() == admin_username && password->text() == admin_password)
        {
            Window::isAdmin = true;
            window = new Window();
            window->show();
            this->close();
        }
        else
        {
            QMessageBox box;
            box.setText("Incorrect login credentials!");
            box.exec();
        }
    }
    else
    {
        Window::isAdmin = false;
        window = new Window();
        window->show();
        this->close();
    }

}
