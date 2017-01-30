QT = core qml network gui quick widgets quickwidgets multimedia
TARGET = rotable-client

CONFIG += precompile_header c++11
PRECOMPILED_HEADER = private/precomp.h

QMAKE_CFLAGS_RELEASE = -g

win32:CONFIG += windows

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
    include/callwaiter.h \
    include/queue.h \
    private/precomp.h \
    include/playadvertising.h \
    include/touchevent.h \
    include/mediaplayer.h

SOURCES += \
    source/main.cpp \
    source/configclient.cpp \
    source/sensors.cpp \
    source/tcpclient.cpp \
    source/client.cpp \
    source/categorylistmodel.cpp \
    source/productlistmodel.cpp \
    source/imageprovider.cpp \
    source/callwaiter.cpp \
    source/queue.cpp \
    source/playadvertising.cpp \
    source/touchevent.cpp \
    source/mediaplayer.cpp


RESOURCES +=\
    resources.qrc \
    $$PWD/../shared/shared_resources.qrc

OTHER_FILES += \
    qml/client/main.qml \
    qml/client/ProductButton.qml \
    qml/client/ProductCategoryPage.qml \
    qml/client/CategoryBar.qml \
    qml/client/ConnectionPage.qml \
    qml/client/ScreensaverPage.qml \
    qml/client/StartPage.qml \
    qml/client/MyOrderButton.qml \
    qml/client/MyOrderPage.qml \
    qml/client/MyOrderRects.qml \
    qml/client/ProductRects.qml \
    qml/client/ProductPage.qml \
    qml/client/callWaiter/CallWaiterPage.qml\
    qml/client_LB/main.qml \
    qml/client_LB/ProductButton.qml \
    qml/client_LB/ProductCategoryPage.qml \
    qml/client_LB/CategoryBar.qml \
    qml/client_LB/ConnectionPage.qml \
    qml/client_LB/ScreensaverPage.qml \
    qml/client_LB/StartPage.qml \
    qml/client_LB/MyOrderButton.qml \
    qml/client_LB/MyOrderPage.qml \
    qml/client_LB/ProductRects.qml \
    qml/client_LB/ProductPage.qml

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
                   #/home/mateus/raspi//rootfs/usr/include \

    LIBS += \
            -L/home/rosynski/opt/third_party/wiringPi/wiringPi -lwiringPi \
            -L/home/rosynski/opt/rpi/rasp-pi-rootfs/usr/include -lrt
           #-L$$PWD/../third-party/wiringPi/wiringPi -lwiringPi #\
        #-L$$PWD/../third-party/google-breakpad-read-only-rpi/src/client/linux -lbreakpad_client
}

win32{
    PLATFORM = host

    INCLUDEPATH -= /home/rosynski/opt/third_party/wiringPi/wiringPi \#$$PWD/../third-party/wiringPi/wiringPi \
                   /home/rosynski/opt/rpi/rootfs/usr/include \

    LIBS -= \
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

win32:LIBS += -lws2_32

target.path = /opt/rotable
INSTALLS    += target

DISTFILES += \
#    qml/client/callWaiter/CallWaiterPage.qml

########################################################################
# TRANSLATION:


