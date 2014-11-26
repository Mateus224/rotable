QT = core network sql gui
TARGET = rotable-server

CONFIG   += console debug precompile_header
CONFIG   -= app_bundle

PRECOMPILED_HEADER = private/precomp.h

QMAKE_CFLAGS_RELEASE = -g

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
    source/server.cpp

HEADERS += \
    include/tcpserver.h \
    include/database.h \
    include/configserver.h \
    private/precomp.h \
    include/server.h \
    include/settings.h

########################################################################
# DESTINATION:

contains(QMAKE_CC, gcc) {
    debug:ROTABLE_DEST = debug/host
    release:ROTABLE_DEST = release/host

    LIBS += -lbreakpad_client
} else {
    debug:ROTABLE_DEST = debug/rpi
    release:ROTABLE_DEST = release/rpi

    LIBS += -lbreakpad_client_rpi
}

DESTDIR     = $$PWD/../bin/$$ROTABLE_DEST
OBJECTS_DIR = $$PWD/../bin/tmp/obj/$$ROTABLE_DEST/$$TARGET
MOC_DIR     = $$PWD/../bin/tmp/moc/$$ROTABLE_DEST/$$TARGET
RCC_DIR     = $$PWD/../bin/tmp/rcc/$$ROTABLE_DEST/$$TARGET
UI_DIR      = $$PWD/../bin/tmp/ui/$$ROTABLE_DEST/$$TARGET

LIBS += \
    -L$$DESTDIR -lrotable-shared \
    -L$$PWD/../third-party/google-breakpad-read-only/src/client/linux
