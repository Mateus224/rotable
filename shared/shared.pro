QT += core network sql xml qml

TARGET = rotable-shared
TEMPLATE = lib

CONFIG += staticlib precompile_header  c++11
PRECOMPILED_HEADER = private/precomp.h
QMAKE_CXXFLAGS += -std=c++11

########################################################################
# FILES:

INCLUDEPATH += include

SOURCES += \
    source/productcategory.cpp \
    source/product.cpp \
    source/configbase.cpp \
    source/compackage.cpp \
    source/utils.cpp \
    source/productcontainer.cpp \
    source/productorder.cpp \
    source/logmanager.cpp \
    source/order.cpp \
    source/income.cpp \
    source/config.cpp \
    #source/mytables.cpp \
    source/productorderlistmodel.cpp \
    source/client.cpp \
    source/tabele.cpp \
    source/message.cpp \
    source/messageconnector.cpp \
    source/languagesupport.cpp \
    source/waiter_client.cpp \
    source/filecontainer/imagecontainer.cpp \
    source/batteryinfo.cpp \
    source/filecontainer/advertisingvideo.cpp \
    source/filecontainer/file.cpp \
    source/filecontainer/advertisingcontainer.cpp \
    source/systemupdate.cpp



HEADERS += \
    include/configbase.h \
    include/product.h \
    include/productcategory.h \
    include/compackage.h \
    include/utils.h \
    include/productcontainer.h \
    include/productorder.h \
    include/logmanager.h \
    include/loglistenerremote.h \
    include/loglisternerstdout.h \
    include/loglistenerfileout.h \
    include/order.h \
    include/income.h \
    include/config.h \
    #include/mytables.h \
    include/productorderlistmodel.h \
    include/client.h \
    include/waiter.h \
    include/table.h \
    include/message.h \
    include/messageconnector.h \
    include/languagesupport.h \
    include/filecontainer/imagecontainer.h \
    include/batteryinfo.h \
    include/filecontainer/advertisingvideo.h \
    include/filecontainer/file.h \
    include/filecontainer/advertisingcontainer.h \
    include/systemupdate.h



RESOURCES += shared_resources.qrc

########################################################################
# DESTINATION:

win32{
    PLATFORM = host
}
else{
    contains(QMAKE_CC, gcc) {
        PLATFORM = host
    } else {
        # since QMAKE_CC contains more than gcc this must be a cross-compile build
        PLATFORM = rpi
    }
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
