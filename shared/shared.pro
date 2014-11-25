QT += core network sql xml

TARGET = rotable-shared
TEMPLATE = lib
CONFIG += staticlib precompile_header
PRECOMPILED_HEADER = private/precomp.h

INCLUDEPATH += include

########################################################################
# FILES:

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

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}

contains(QMAKE_CC, gcc) {
    debug:ROTABLE_DEST = debug/host/$$TARGET
    release:ROTABLE_DEST = release/host/$$TARGET
} else {
    debug:ROTABLE_DEST = debug/rpi/$$TARGET
    release:ROTABLE_DEST = release/rpi/$$TARGET
}

DESTDIR     = ../../bin/$$ROTABLE_DEST
OBJECTS_DIR = ../../bin/tmp/obj/$$ROTABLE_DEST
MOC_DIR     = ../../bin/tmp/moc/$$ROTABLE_DEST
RCC_DIR     = ../../bin/tmp/rcc/$$ROTABLE_DEST
UI_DIR      = ../../bin/tmp/ui/$$ROTABLE_DEST
