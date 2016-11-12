QT = core qml network gui quick widgets
TARGET = rotable-waiter_03

CONFIG += precompile_header
PRECOMPILED_HEADER = private/precomp.h

QMAKE_CFLAGS_RELEASE = -g

win32:CONFIG += windows

########################################################################
# FILES:

INCLUDEPATH += \
    include \
    $$PWD/../shared/include \
    $$PWD/../third-party/google-breakpad-read-only/src

HEADERS += \
    include/tablemodel.h \
    include/configwaiter.h \
    include/tcpclient.h \
    include/waiter_client.h \
    include/orderboard.h \
    include/productlist.h \
    include/neededboard.h \
    include/orderhistory.h \
    include/proxymodelevententries.h


SOURCES += \
    source/main.cpp \
    source/configwaiter.cpp \
    source/tcpclient.cpp \
    source/waiter_client.cpp \
    source/tablemodel.cpp \
    source/orderboard.cpp \
    source/productlist.cpp \
    source/neededboard.cpp \
    source/orderhistory.cpp \
    source/proxymodelevententries.cpp

RESOURCES +=\
    resources.qrc \
    $$PWD/../shared/shared_resources.qrc

########################################################################
# DESTINATION:

contains(QMAKE_CC, gcc) {
    PLATFORM = host

    LIBS += \
   #     -lbreakpad_client \
   #     -L$$PWD/../third-party/google-breakpad-read-only/src/client/linux
} else {
    # since QMAKE_CC contains more than gcc this must be a cross-compile build
    PLATFORM = rpi

    LIBS += \
 #       -lbreakpad_client
 #       -L$$PWD/../third-party/google-breakpad-read-only-rpi/src/client/linux
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
    resources/qml/main.qml \
    resources/qml/LoginView.qml \
    resources/qml/WaiterView.qml \
    resources/qml/DataView.qml \
    resources/qml/PullOutMenu/PullOutMenu.qml \
    resources/qml/PullOutMenu/PullOutMenuElement.qml \
    resources/qml/PullOutMenu/PullOutMenuModel.qml \
    resources/qml/TablesView/TablesView.qml \
    resources/qml/TablesView/TableList.qml \
    resources/qml/TablesView/TableListElement.qml \
    resources/qml/TablesView/OrderList.qml \
    resources/qml/TablesView/OrderListElement.qml \
    resources/qml/TablesView/OrderProductListElement.qml \
    resources/qml/TablesView/OutgoingList.qml \
    resources/qml/TablesView/RightPanel.qml \
    resources/qml/TopBar/TimeBar.qml \
    resources/qml/TopBar/SimpleClock.qml \
    resources/qml/BottomBar/BottomBar.qml \
    resources/qml/BottomBar/TableNeedsWaiterList.qml \
    resources/qml/BottomBar/TableNeedsWaiterListElement.qml \
    resources/qml/TopBar/BatteryIcon.qml

########################################################################
# TRANSLATION:

TRANSLATIONS =  localisation/waiter_pl.ts \
                localisation/waiter_de.ts
