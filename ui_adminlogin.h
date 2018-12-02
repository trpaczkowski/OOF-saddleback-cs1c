/********************************************************************************
** Form generated from reading UI file 'adminlogin.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINLOGIN_H
#define UI_ADMINLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminLogin
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_3;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_user;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_pass;

    void setupUi(QDialog *AdminLogin)
    {
        if (AdminLogin->objectName().isEmpty())
            AdminLogin->setObjectName(QStringLiteral("AdminLogin"));
        AdminLogin->resize(400, 300);
        buttonBox = new QDialogButtonBox(AdminLogin);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_3 = new QLabel(AdminLogin);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(160, 40, 111, 31));
        layoutWidget = new QWidget(AdminLogin);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 70, 261, 101));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit_user = new QLineEdit(layoutWidget);
        lineEdit_user->setObjectName(QStringLiteral("lineEdit_user"));

        horizontalLayout_2->addWidget(lineEdit_user);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_pass = new QLineEdit(layoutWidget);
        lineEdit_pass->setObjectName(QStringLiteral("lineEdit_pass"));
        lineEdit_pass->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(lineEdit_pass);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(AdminLogin);
        QObject::connect(buttonBox, SIGNAL(accepted()), AdminLogin, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AdminLogin, SLOT(reject()));

        QMetaObject::connectSlotsByName(AdminLogin);
    } // setupUi

    void retranslateUi(QDialog *AdminLogin)
    {
        AdminLogin->setWindowTitle(QApplication::translate("AdminLogin", "Dialog", nullptr));
        label_3->setText(QApplication::translate("AdminLogin", "Administrator Login", nullptr));
        label->setText(QApplication::translate("AdminLogin", "Username", nullptr));
        label_2->setText(QApplication::translate("AdminLogin", "Password ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminLogin: public Ui_AdminLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINLOGIN_H
