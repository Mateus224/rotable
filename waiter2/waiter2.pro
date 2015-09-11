QT = core qml network gui quick #declarative
TARGET = rotable-waiter_02

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
    include/configwaiter.h \
    include/tcpwaiter.h \
    include/tcpclient.h \
    #include/qmlcontxt.h \
    include/waiter_client.h \
    include/orderboard.h \
    include/tablemodel.h \
    include/productlist.h


SOURCES += \
    source/main.cpp \
    source/configwaiter.cpp \
    source/tcpclient.cpp \
    #source/qmlcontxt.cpp \
    source/waiter_client.cpp \
    source/tablemodel.cpp \
    source/orderboard.cpp \
    source/productlist.cpp

RESOURCES +=\
    resources.qrc \
    $$PWD/../shared/shared_resources.qrc

OTHER_FILES += \
    qml/waiter/main.qml \
    qml/waiter/componentCreation.js \
    qml/waiter/TableButton.qml \
    qml/waiter/TestQml.qml

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

DISTFILES += \
    qml/waiter/main2.qml \
    qml/waiter/TableList.qml \
    qml/waiter/OrderList.qml \
    qml/waiter/Menu.qml \
    qml/waiter/main3.qml \
    qml/waiter/Label.qml \
    qml/waiter/TableButton.qml
