QT += core gui network qml widgets

TARGET = rotable-admin
TEMPLATE = app

CONFIG += precompile_header
PRECOMPILED_HEADER = private/precomp.h

QMAKE_CFLAGS_RELEASE = -g

########################################################################
# FILES:

INCLUDEPATH += \
    ../shared/include \
    include \
    ../google-breakpad \
    ../qwt/src

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

########################################################################
# LINK:

LIBS += \
    -L$$DESTDIR/../rotable-shared -lrotable-shared \
    -L$$DESTDIR/../../../../google-breakpad -lbreakpad_client_x86 \
    -L$$DESTDIR/../../../../qwt/lib -lqwt
