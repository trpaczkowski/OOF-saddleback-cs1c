#-------------------------------------------------
#
# Project created by QtCreator 2018-11-06T17:41:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OOF
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    adminlogin.cpp \
    shape.cpp \
<<<<<<< HEAD
    canvas.cpp \
    contactwindow.cpp
=======
    canvas.cpp
>>>>>>> f10f7fc401ffd2c2bc22c0dc688ad62b4db56600

HEADERS += \
        mainwindow.h \
    adminlogin.h \
    shape.h \
    vector.h \
<<<<<<< HEAD
    canvas.h \
    contactwindow.h

FORMS += \
        mainwindow.ui \
    adminlogin.ui \
    contactwindow.ui
=======
    canvas.h

FORMS += \
        mainwindow.ui \
    adminlogin.ui
>>>>>>> f10f7fc401ffd2c2bc22c0dc688ad62b4db56600
