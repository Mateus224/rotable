QT += core gui network qml widgets

TARGET = rotable-admin
TEMPLATE = app

CONFIG += precompile_header
PRECOMPILED_HEADER = private/precomp.h

QMAKE_CFLAGS_RELEASE = -g

########################################################################
# FILES:

INCLUDEPATH += \
    include \
    $$PWD/../shared/include \
    $$PWD/../third-party/google-breakpad-read-only/src \
    $$PWD/../third-party/qwt/src

SOURCES += \
    source/main.cpp \
    source/mainwindow.cpp \
    source/orderlistview.cpp \
    source/tcpclient.cpp \
    source/executor.cpp \
    source/controller.cpp \
    source/connecttoserverdialog.cpp \
    source/configadmin.cpp \
    source/addproductcategory.cpp \
    source/producttableview.cpp \
    source/categorylistview.cpp \
    source/categorylistmodel.cpp \
    source/producttablemodel.cpp \
    source/addproductdialog.cpp \
    source/statistik_plot.cpp \
    source/date.cpp \
    source/io_writeinmonthwithnewdata.cpp \
    source/iodevicefordata.cpp \
    source/io_readfordiagram.cpp \
    source/io_init.cpp \
    source/serverloglistener.cpp \
    source/producttableiconcomboboxdelegate.cpp

HEADERS += \
    include/mainwindow.h \
    include/orderlistview.h \
    include/tcpclient.h \
    include/executor.h \
    include/controller.h \
    include/connecttoserverdialog.h \
    include/configadmin.h \
    include/addproductcategory.h \
    include/producttableview.h \
    include/categorylistview.h \
    include/categorylistmodel.h \
    include/producttablemodel.h \
    include/addproductdialog.h \
    include/statistik_plot.h \
    include/date.h \
    include/io_writeinmonthwithnewdata.h \
    include/iodevicefordata.h \
    include/io_readfordiagram.h \
    include/io_init.h \
    include/serverloglistener.h \
    include/producttableiconcomboboxdelegate.h \
    private/precomp.h

FORMS += \
    ui/mainwindow.ui \
    ui/connectToServer.ui \
    ui/addproductdialog.ui \
    ui/addproductcategorydialog.ui

RESOURCES += \
    resources/resources.qrc \
    ../shared/shared_resources.qrc

########################################################################
# DESTINATION:

contains(QMAKE_CC, gcc) {
    debug:ROTABLE_DEST = debug/host
    release:ROTABLE_DEST = release/host
} else {
    debug:ROTABLE_DEST = debug/rpi
    release:ROTABLE_DEST = release/rpi
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
    -L$$PWD/../third-party/google-breakpad-read-only/src/client/linux -lbreakpad_client \
    -L$$PWD/../third-party/qwt/lib -lqwt
