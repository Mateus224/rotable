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
    include/imageprovider.h \
    include/orderlistmodel.h

SOURCES += \
    source/main.cpp \
    source/configclient.cpp \
    source/sensors.cpp \
    source/tcpclient.cpp \
    source/client.cpp \
    source/categorylistmodel.cpp \
    source/productlistmodel.cpp \
    source/imageprovider.cpp \
    source/orderlistmodel.cpp


RESOURCES +=\
    resources.qrc \
    $$PWD/../shared/shared_resources.qrc

OTHER_FILES += \
    qml/client/categoryCreation.js \
    qml/client/main.qml \
    qml/client/ProductButton.qml \
    qml/client/ProductCategoryPage.qml \
    qml/client/CategoryBar.qml \
    qml/client/ConnectionPage.qml \
    qml/client/ScreensaverPage.qml \
    qml/client/StartPage.qml \
    qml/client/MyOrderButton.qml \
    qml/client/MyOrderPage.qml \
    qml/client/ProductRects.qml \
    qml/client/ProductPage.qml

########################################################################
# DESTINATION:

contains(QMAKE_CC, gcc) {
    PLATFORM = host

    LIBS += \
       # -lbreakpad_client \
       # -L$$PWD/../third-party/google-breakpad-read-only/src/client/linux
} else {
    # since QMAKE_CC contains more than gcc this must be a cross-compile build
    PLATFORM = rpi

    INCLUDEPATH += /home/rosynski/opt/third_party/wiringPi/wiringPi \#$$PWD/../third-party/wiringPi/wiringPi \
                   /home/rosynski/opt/rpi/rootfs/usr/include \

    LIBS += \
            -L/home/rosynski/opt/third_party/wiringPi/wiringPi -lwiringPi \
            -L/home/rosynski/opt/rpi/rasp-pi-rootfs/usr/include -lrt
           #-L$$PWD/../third-party/wiringPi/wiringPi -lwiringPi #\
        #-L$$PWD/../third-party/google-breakpad-read-only-rpi/src/client/linux -lbreakpad_client
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

########################################################################
# LINK:

LIBS += \
    -L$$DESTDIR -lrotable-shared

target.path = /opt/rotable
INSTALLS    += target
