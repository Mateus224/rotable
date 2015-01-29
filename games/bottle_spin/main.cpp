#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //QtQuick2ApplicationViewer viewer;

    //QString qml(QString("qrc:/bottlespin/main.qml"));

    //viewer.setSource(QString("qrc:/bottlespin/main.qml"));
    //viewer.showExpanded();

    QQuickView view;

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QString("qrc:/bs/main.qml"));
    view.show();

    return app.exec();
}




