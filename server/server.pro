QT = core network sql gui
TARGET = rotable_server

CONFIG   += console debug precompile_header
CONFIG   -= app_bundle

PRECOMPILED_HEADER = private/precomp.h

SOURCES += \
    source/main.cpp \
    source/tcpserver.cpp \
    source/database.cpp \
    source/configserver.cpp \
    source/server.cpp

HEADERS += \
    include/tcpserver.h \
    include/database.h \
    include/configserver.h \
    private/precomp.h \
    include/server.h \
    include/settings.h

INCLUDEPATH += \
    ../shared/include include \
    ../google-breakpad

contains(QMAKE_CC, gcc) {
    debug:ROTABLE_DEST = debug/host/$$TARGET
    release:ROTABLE_DEST = release/host/$$TARGET

    LIBS += -lbreakpad_client_x86
} else {
    debug:ROTABLE_DEST = debug/rpi/$$TARGET
    release:ROTABLE_DEST = release/rpi/$$TARGET

    LIBS += -lbreakpad_client_rpi
}

DESTDIR     = ../../software/bin/$$ROTABLE_DEST
OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR     = $$DESTDIR/moc
RCC_DIR     = $$DESTDIR/rcc
UI_DIR      = $$DESTDIR/ui

LIBS += -L$$DESTDIR/../shared -lshared \
        -L../../software/google-breakpad

#PRE_TARGETDEPS += $$DESTDIR/../shared/libshared.a
