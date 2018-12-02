/********************************************************************************
** Form generated from reading UI file 'contactwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTACTWINDOW_H
#define UI_CONTACTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_contactwindow
{
public:
    QLabel *logo;
    QLabel *teamName;
    QLabel *taylor;
    QLabel *taylor_email;
    QLabel *jeff;
    QLabel *jess_email;
    QLabel *travis;
    QLabel *travis_email;
    QLabel *caroline;
    QLabel *caroline_email;
    QLabel *utkarsh;
    QLabel *utkarsh_email;
    QLabel *oscar;
    QLabel *oscar_email;
    QLabel *isaac;
    QLabel *isaac_email;

    void setupUi(QDialog *contactwindow)
    {
        if (contactwindow->objectName().isEmpty())
            contactwindow->setObjectName(QStringLiteral("contactwindow"));
        contactwindow->setWindowModality(Qt::WindowModal);
        contactwindow->resize(802, 299);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(contactwindow->sizePolicy().hasHeightForWidth());
        contactwindow->setSizePolicy(sizePolicy);
        contactwindow->setMinimumSize(QSize(0, 0));
        contactwindow->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(8);
        contactwindow->setFont(font);
        contactwindow->setSizeGripEnabled(true);
        contactwindow->setModal(false);
        logo = new QLabel(contactwindow);
        logo->setObjectName(QStringLiteral("logo"));
        logo->setGeometry(QRect(60, 20, 171, 181));
        logo->setPixmap(QPixmap(QString::fromUtf8("oof logo.jpg")));
        logo->setScaledContents(true);
        teamName = new QLabel(contactwindow);
        teamName->setObjectName(QStringLiteral("teamName"));
        teamName->setEnabled(true);
        teamName->setGeometry(QRect(20, 180, 300, 30));
        teamName->setMinimumSize(QSize(100, 30));
        QFont font1;
        font1.setPointSize(12);
        teamName->setFont(font1);
        teamName->setFrameShape(QFrame::NoFrame);
        taylor = new QLabel(contactwindow);
        taylor->setObjectName(QStringLiteral("taylor"));
        taylor->setGeometry(QRect(530, 170, 201, 16));
        taylor_email = new QLabel(contactwindow);
        taylor_email->setObjectName(QStringLiteral("taylor_email"));
        taylor_email->setGeometry(QRect(530, 190, 251, 31));
        jeff = new QLabel(contactwindow);
        jeff->setObjectName(QStringLiteral("jeff"));
        jeff->setGeometry(QRect(300, 20, 131, 31));
        jess_email = new QLabel(contactwindow);
        jess_email->setObjectName(QStringLiteral("jess_email"));
        jess_email->setGeometry(QRect(300, 50, 201, 31));
        travis = new QLabel(contactwindow);
        travis->setObjectName(QStringLiteral("travis"));
        travis->setGeometry(QRect(300, 160, 201, 31));
        travis_email = new QLabel(contactwindow);
        travis_email->setObjectName(QStringLiteral("travis_email"));
        travis_email->setGeometry(QRect(300, 190, 221, 31));
        caroline = new QLabel(contactwindow);
        caroline->setObjectName(QStringLiteral("caroline"));
        caroline->setGeometry(QRect(460, 240, 161, 16));
        caroline_email = new QLabel(contactwindow);
        caroline_email->setObjectName(QStringLiteral("caroline_email"));
        caroline_email->setGeometry(QRect(440, 260, 201, 16));
        utkarsh = new QLabel(contactwindow);
        utkarsh->setObjectName(QStringLiteral("utkarsh"));
        utkarsh->setGeometry(QRect(300, 100, 141, 16));
        utkarsh_email = new QLabel(contactwindow);
        utkarsh_email->setObjectName(QStringLiteral("utkarsh_email"));
        utkarsh_email->setGeometry(QRect(300, 120, 221, 31));
        oscar = new QLabel(contactwindow);
        oscar->setObjectName(QStringLiteral("oscar"));
        oscar->setGeometry(QRect(530, 100, 161, 16));
        oscar_email = new QLabel(contactwindow);
        oscar_email->setObjectName(QStringLiteral("oscar_email"));
        oscar_email->setGeometry(QRect(530, 120, 191, 31));
        isaac = new QLabel(contactwindow);
        isaac->setObjectName(QStringLiteral("isaac"));
        isaac->setGeometry(QRect(530, 30, 151, 16));
        isaac_email = new QLabel(contactwindow);
        isaac_email->setObjectName(QStringLiteral("isaac_email"));
        isaac_email->setGeometry(QRect(530, 50, 211, 31));

        retranslateUi(contactwindow);

        QMetaObject::connectSlotsByName(contactwindow);
    } // setupUi

    void retranslateUi(QDialog *contactwindow)
    {
        contactwindow->setWindowTitle(QApplication::translate("contactwindow", "Dialog", nullptr));
        logo->setText(QString());
        teamName->setText(QApplication::translate("contactwindow", "Object Oriented Friends", nullptr));
        taylor->setText(QApplication::translate("contactwindow", "Taylor Paczkowski", nullptr));
        taylor_email->setText(QApplication::translate("contactwindow", "tpaczkowski0@saddleback.edu", nullptr));
        jeff->setText(QApplication::translate("contactwindow", "Jeffery Adams", nullptr));
        jess_email->setText(QApplication::translate("contactwindow", "jadams62@saddleback.edu", nullptr));
        travis->setText(QApplication::translate("contactwindow", "Travis Nguyen", nullptr));
        travis_email->setText(QApplication::translate("contactwindow", "tnguyen603@saddleback.edu", nullptr));
        caroline->setText(QApplication::translate("contactwindow", "Caroline Ta", nullptr));
        caroline_email->setText(QApplication::translate("contactwindow", "tta242saddleback.edu", nullptr));
        utkarsh->setText(QApplication::translate("contactwindow", "Utkarsh Karki", nullptr));
        utkarsh_email->setText(QApplication::translate("contactwindow", "ukarki0@saddleback.edu", nullptr));
        oscar->setText(QApplication::translate("contactwindow", "Oscar Lopez", nullptr));
        oscar_email->setText(QApplication::translate("contactwindow", "olopez23@saddleback.edu", nullptr));
        isaac->setText(QApplication::translate("contactwindow", "Isaac Estrada", nullptr));
        isaac_email->setText(QApplication::translate("contactwindow", "iestrada5@saddleback.edu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class contactwindow: public Ui_contactwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTACTWINDOW_H
