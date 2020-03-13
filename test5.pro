#-------------------------------------------------
#
# Project created by QtCreator 2018-11-20T10:32:19
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    searchdialog.cpp \
    showinfo.cpp \
    addinfo.cpp \
    loginin.cpp

HEADERS  += mainwindow.h \
    searchdialog.h \
    showinfo.h \
    addinfo.h \
    loginin.h

FORMS    += mainwindow.ui \
    searchdialog.ui \
    showinfo.ui \
    addinfo.ui \
    loginin.ui

RESOURCES += \
    images.qrc
