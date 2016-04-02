QT += core
QT -= gui

CONFIG += c++11

TARGET = RSAKeyGenerator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

QMAKE_CXXFLAGS += -lcryptopp

LIBS += -L/usr/lib/crypto++ -lcryptopp
INCS += -I/usr/include/crypto++

DEFINES += "PWD_PRO=$$_PRO_FILE_PWD_"



