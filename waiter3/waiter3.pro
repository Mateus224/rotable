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
    include/orderhistory.h


SOURCES += \
    source/main.cpp \
    source/configwaiter.cpp \
    source/tcpclient.cpp \
    source/waiter_client.cpp \
    source/tablemodel.cpp \
    source/orderboard.cpp \
    source/productlist.cpp \
    source/neededboard.cpp \
    source/orderhistory.cpp

RESOURCES +=\
    resources.qrc \
    $$PWD/../shared/shared_resources.qrc

OTHER_FILES += \
    qml/waiter/main.qml \
    qml/waiter/LoginView.qml \
    qml/waiter/WaiterView.qml \
    qml/waiter/PullOutMenu.qml \
    qml/waiter/PullOutMenuElement.qml \
    qml/waiter/PullOutMenuModel.qml \
    qml/waiter/DataView.qml \
    qml/waiter/TablesView.qml \
    qml/waiter/TableList.qml \
    qml/waiter/TableListElement.qml \
    qml/waiter/OrderList.qml \
    qml/waiter/OrderListElement.qml \
    qml/waiter/OrderProductListElement.qml \
    qml/waiter/OutgoingList.qml \
    qml/waiter/TimeBar.qml \
    qml/waiter/SimpleClock.qml \
    qml/waiter/BottomBar.qml \
    qml/waiter/RightPanel.qml \
    qml/waiter/TableNeedsWaiterList.qml \
    qml/waiter/TableNeedsWaiterListElement.qml

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
    qml/waiter/main.qml \
    qml/waiter/LoginView.qml \
    qml/waiter/WaiterView.qml \
    qml/waiter/PullOutMenu.qml \
    qml/waiter/PullOutMenuElement.qml \
    qml/waiter/PullOutMenuModel.qml \
    qml/waiter/DataView.qml \
    qml/waiter/TablesView.qml \
    qml/waiter/TableList.qml \
    qml/waiter/TableListElement.qml \
    qml/waiter/OrderList.qml \
    qml/waiter/OrderListElement.qml \
    qml/waiter/OrderProductListElement.qml \
    qml/waiter/OutgoingList.qml \
    qml/waiter/TimeBar.qml \
    qml/waiter/SimpleClock.qml \
    qml/waiter/BottomBar.qml \
    qml/waiter/RightPanel.qml \
    qml/waiter/TableNeedsWaiterList.qml \
    qml/waiter/TableNeedsWaiterListElement.qml

########################################################################
# TRANSLATION:

TRANSLATIONS =  localisation/waiter_pl.ts \
                localisation/waiter_de.ts
