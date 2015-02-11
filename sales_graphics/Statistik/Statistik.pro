#-------------------------------------------------
#
# Project created by QtCreator 2014-04-17T20:05:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Statistik
TEMPLATE = app


SOURCES += main.cpp \
    date.cpp \
    statistik_plot.cpp \
    io_init.cpp \
    io_readfordiagram.cpp \
    iodevicefordata.cpp \
    io_writeinmonthwithnewdata.cpp

HEADERS  += \
    date.h \
    statistik_plot.h \
    iodevicefordata.h \
    io_init.h \
    io_readfordiagram.h \
    io_writeinmonthwithnewdata.h


#LIBS += -L /usr/local/qwt-6.1.1-svn/lib -lqwt
#INCLUDEPATH += /usr/local/qwt-6.1.1-svn/include
#DEPENDPATH += /usr/local/qwt-6.1.1-svn/include

LIBS += -L/home/rosynski/qwt-6.1/lib -lqwt
INCLUDEPATH += /usr/local/qwt-6.1.3-svn/include
DEPENDPATH += /usr/local/qwt-6.1.3-svn/include
