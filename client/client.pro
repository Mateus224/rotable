QT = core qml network gui quick
TARGET = rotable-client

CONFIG += precompile_header
PRECOMPILED_HEADER = private/precomp.h

QMAKE_CFLAGS_RELEASE = -g

########################################################################
# FILES:

INCLUDEPATH += \
    include \
    $$PWD/../shared/include \
    $$PWD/../third-party/google-breakpad-read-only/src \

HEADERS += \
    include/configclient.h \
    include/sensors.h \
    include/tcpclient.h \
    include/settings.h \
    include/client.h \
    include/categorylistmodel.h \
    include/productlistmodel.h \
    include/imageprovider.h

SOURCES += \
    source/main.cpp \
    source/configclient.cpp \
    source/sensors.cpp \
    source/tcpclient.cpp \
    source/client.cpp \
    source/categorylistmodel.cpp \
    source/productlistmodel.cpp \
    source/imageprovider.cpp

RESOURCES +=\
    resources.qrc \
    $$PWD/../shared/shared_resources.qrc

OTHER_FILES += \
    qml/client/categoryCreation.js \
    qml/client/main.qml \
    qml/client/ProductButton.qml \
    qml/client/ProductCategoryPage.qml \
    qml/client/TabWidget.qml \
    qml/client/ConnectionPage.qml

########################################################################
# DESTINATION:

contains(QMAKE_CC, gcc) {
    debug:ROTABLE_DEST = debug/host
    release:ROTABLE_DEST = release/host

    LIBS += \
        -lbreakpad_client \
        -L$$PWD/../third-party/google-breakpad-read-only/src/client/linux
} else {
    debug:ROTABLE_DEST = debug/rpi
    release:ROTABLE_DEST = release/rpi

    INCLUDEPATH += $$PWD/../third-party/wiringPi/wiringPi
    LIBS += \
        -L$$PWD/../third-party/wiringPi/wiringPi -lwiringPi \
        -L$$PWD/../third-party/google-breakpad-read-only-rpi/src/client/linux -lbreakpad_client
}

DESTDIR     = $$PWD/../bin/$$ROTABLE_DEST
OBJECTS_DIR = $$PWD/../bin/tmp/obj/$$ROTABLE_DEST/$$TARGET
MOC_DIR     = $$PWD/../bin/tmp/moc/$$ROTABLE_DEST/$$TARGET
RCC_DIR     = $$PWD/../bin/tmp/rcc/$$ROTABLE_DEST/$$TARGET
UI_DIR      = $$PWD/../bin/tmp/ui/$$ROTABLE_DEST/$$TARGET

########################################################################
# LINK:

LIBS += \
    -L$$DESTDIR -lrotable-shared \
