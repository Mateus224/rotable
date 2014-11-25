TARGET = rotable_client
CONFIG += precompile_header
PRECOMPILED_HEADER = private/precomp.h
QT = core qml network gui quick

QMAKE_CFLAGS_RELEASE = -g

INCLUDEPATH += \
    ../shared/include \
    include \
    ../google-breakpad

HEADERS += \
    include/configclient.h \
    include/sensors.h \
    include/tcpclient.h \
    include/settings.h \
    include/client.h \
    include/categorylistmodel.h \
    include/productlistmodel.h \
    include/imageprovider.h

SOURCES += \
    source/main.cpp \
    source/configclient.cpp \
    source/sensors.cpp \
    source/tcpclient.cpp \
    source/client.cpp \
    source/categorylistmodel.cpp \
    source/productlistmodel.cpp \
    source/imageprovider.cpp

contains(QMAKE_CC, gcc) {
    debug:ROTABLE_DEST = debug/host/$$TARGET
    release:ROTABLE_DEST = release/host/$$TARGET

    LIBS += -lbreakpad_client_x86
} else {
    debug:ROTABLE_DEST = debug/rpi/$$TARGET
    release:ROTABLE_DEST = release/rpi/$$TARGET

    INCLUDEPATH += ../wiringPi/wiringPi
    LIBS += -L../wiringPi/wiringPi -lwiringPi -lbreakpad_client_rpi
}

DESTDIR     = ../../software/bin/$$ROTABLE_DEST
OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR     = $$DESTDIR/moc
RCC_DIR     = $$DESTDIR/rcc
UI_DIR      = $$DESTDIR/ui

LIBS += -L$$DESTDIR/../shared -lshared -L../../software/google-breakpad

contains(QMAKE_CC, gcc) {
  folder.source = qml
  folder.target = $$DESTDIR
  DEPLOYMENTFOLDERS = folder
} else {
  folder.source = qml
  folder.target = $$ROTABLE_DEST
  DEPLOYMENTFOLDERS = folder
}

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    ProductButton.qml \
    qml/etClient/categoryCreation.js \
    qml/etClient/main.qml \
    qml/etClient/ProductButton.qml \
    qml/etClient/ProductCategoryPage.qml \
    qml/etClient/TabWidget.qml \
    qml/client/ConnectionPage.qml

#PRE_TARGETDEPS += $$DESTDIR/../shared/libshared.a

RESOURCES += resources.qrc ../shared/shared_resources.qrc
