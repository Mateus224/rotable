#-------------------------------------------------
#
# Project created by QtCreator 2016-04-02T09:36:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LicenceGenerator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES +=

LIBS += -L/usr/lib/crypto++ -lcryptopp
INCS += -I/usr/include/crypto++
