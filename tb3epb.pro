#-------------------------------------------------
#
# Project created by QtCreator 2016-09-07T15:55:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tb3epb
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    maindialog.cpp \
    projecthandler.cpp \
    texhighlighter.cpp

HEADERS  += mainwindow.hpp \
    Constants.h \
    maindialog.hpp \
    mainwindow.hpp \
    projecthandler.hpp \
    texhighlighter.hpp

FORMS    += mainwindow.ui \
    maindialog.ui
