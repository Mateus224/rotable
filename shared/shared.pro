QT += core network sql xml qml

TARGET = rotable-shared
TEMPLATE = lib

CONFIG += staticlib precompile_header
PRECOMPILED_HEADER = private/precomp.h

########################################################################
# FILES:

INCLUDEPATH += include

SOURCES += \
    source/productcategory.cpp \
    source/product.cpp \
    source/configbase.cpp \
    source/compackage.cpp \
    source/utils.cpp \
    source/imagecontainer.cpp \
    source/productcontainer.cpp \
    source/productorder.cpp \
    source/logmanager.cpp \
    source/order.cpp \
    source/waiter.cpp \
    source/income.cpp \
    source/config.cpp \
    source/mytables.cpp \
    source/orderinformation.cpp \
    source/qmlcontxt.cpp \
    source/productorderlistmodel.cpp


HEADERS += \
    include/configbase.h \
    include/product.h \
    include/productcategory.h \
    include/compackage.h \
    include/utils.h \
    include/imagecontainer.h \
    include/productcontainer.h \
    include/productorder.h \
    include/logmanager.h \
    include/loglistenerremote.h \
    include/loglisternerstdout.h \
    include/order.h \
    include/waiter.h \
    include/income.h \
    include/config.h \
    include/mytables.h \
    include/orderinformation.h \
    include/qmlcontxt.h \
    include/productorderlistmodel.h \
    include/productorderlistmodel.h


RESOURCES += shared_resources.qrc

########################################################################
# DESTINATION:

contains(QMAKE_CC, gcc) {
    PLATFORM = host
} else {
    # since QMAKE_CC contains more than gcc this must be a cross-compile build
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
