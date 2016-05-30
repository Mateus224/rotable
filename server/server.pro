QT = core network sql gui qml
TARGET = rotable-server

CONFIG   += console precompile_header c++11
CONFIG   -= app_bundle

PRECOMPILED_HEADER = private/precomp.h

QMAKE_CFLAGS_RELEASE = -g
QMAKE_CXXFLAGS += -std=c++11

########################################################################
# FILES:

INCLUDEPATH += \
    $$PWD/../shared/include include \
    $$PWD/../third-party/google-breakpad-read-only/src

SOURCES += \
    source/main.cpp \
    source/tcpserver.cpp \
    source/database.cpp \
    source/configserver.cpp \
    source/server.cpp \
    source/schedule.cpp \
    source/operation.cpp \
    source/licence.cpp

HEADERS += \
    include/tcpserver.h \
    include/database.h \
    include/configserver.h \
    private/precomp.h \
    include/server.h \
    include/settings.h \
    include/schedule.h \
    include/operation.h \
    include/licence.h

########################################################################
# DESTINATION:

contains(QMAKE_CC, gcc) {
 #   LIBS += -lbreakpad_client
    PLATFORM = host
} else {
    # since QMAKE_CC contains more than gcc this must be a cross-compile build
 #   LIBS += -lbreakpad_client_rpi
    PLATFORM = rpi
}

CONFIG(debug, debug|release) {
    DESTDIR     = $$PWD/../bin/debug/$$PLATFORM
    OBJECTS_DIR = $$PWD/../bin/tmp/obj/debug/$$PLATFORM/$$TARGET
    MOC_DIR     = $$PWD/../bin/tmp/moc/debug/$$PLATFORM/$$TARGET
    RCC_DIR     = $$PWD/../bin/tmp/rcc/debug/$$PLATFORM/$$TARGET
    UI_DIR      = $$PWD/../bin/tmp/ui/debug/$$PLATFORM/$$TARGET
} else {
    DESTDIR     = $$PWD/../bin/release/host
    OBJECTS_DIR = $$PWD/../bin/tmp/obj/release/$$PLATFORM/$$TARGET
    MOC_DIR     = $$PWD/../bin/tmp/moc/release/$$PLATFORM/$$TARGET
    RCC_DIR     = $$PWD/../bin/tmp/rcc/release/$$PLATFORM/$$TARGET
    UI_DIR      = $$PWD/../bin/tmp/ui/release/$$PLATFORM/$$TARGET
}

LIBS += \
    -L$$DESTDIR -lrotable-shared \
  #  -L$$PWD/../third-party/google-breakpad-read-only/src/client/linux

win32:LIBS += -lws2_32

RESOURCES += \
    sql-commands.qrc \
    keys.qrc

DISTFILES +=

LIBS += -L/usr/lib/crypto++ -lcryptopp
INCS += -I/usr/include/crypto++

##############################################################################################
# Windows Cryptopp
win32 {
    LIBS -= -L/usr/lib/crypto++ -lcryptopp
    INCS -= -I/usr/include/crypto++

    Debug:LIBS += -L"$$PWD/dependencies/cryptopp/libs/" -lcryptlib-d
    Release:LIBS += -L"$$PWD/dependencies/cryptopp/libs/" -lcryptlib

    Release:PRE_TARGETDEPS += $$PWD/dependencies/cryptopp/libs/cryptlib.lib

    INCLUDEPATH += "$$PWD/dependencies/cryptopp/include"
    DEPENDPATH += "$$PWD/dependencies/cryptopp/include"
}
