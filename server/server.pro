QT = core network sql gui
TARGET = rotable-server

CONFIG   += console precompile_header
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
    LIBS += -lbreakpad_client
    PLATFORM = host
} else {
    # since QMAKE_CC contains more than gcc this must be a cross-compile build
    LIBS += -lbreakpad_client_rpi
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
    -L$$PWD/../third-party/google-breakpad-read-only/src/client/linux

RESOURCES += \
    sql-commands.qrc
