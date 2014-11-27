QT += core network sql xml

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
    source/logmanager.cpp

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
    include/loglisternerstdout.h

RESOURCES += shared_resources.qrc

########################################################################
# DESTINATION:

#message($$QMAKE_CC)

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
