import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    color: "#00000000"


    Image {

        id: logo
        source: "qrc:/images/resources/powered_by_logo_in_e_white.svg"
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
    Queue{

    }
}
