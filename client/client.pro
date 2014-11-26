QT = core qml network gui quick
TARGET = rotable-client

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

RESOURCES +=\
    resources.qrc \
    $$PWD/../shared/shared_resources.qrc

########################################################################
# DESTINATION:

contains(QMAKE_CC, gcc) {
    debug:ROTABLE_DEST = debug/host
    release:ROTABLE_DEST = release/host

    LIBS += -lbreakpad_client
} else {
    debug:ROTABLE_DEST = debug/rpi
    release:ROTABLE_DEST = release/rpi

    INCLUDEPATH += $$PWD/../third-party/wiringPi/wiringPi
    LIBS += -L$$PWD/../third-party/wiringPi/wiringPi -lwiringPi -lbreakpad_client_rpi
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
    -L$$PWD/../third-party/google-breakpad-read-only/src/client/linux

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
