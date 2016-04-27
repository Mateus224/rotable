import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    color: "#00000000"


    Image {

        id: logo
        source: "qrc:/client/resources/rotable_logo.png"
        anchors.top: parent.top
        anchors.bottom: categoryBar.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 1

        width: parent.width
        fillMode: Image.PreserveAspectFit
    }

    MyOrderButton{

    }
    CategoryBar {
        id: categoryBar
    }
}
