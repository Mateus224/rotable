import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    color: "#00000000"

    MyOrderButton {
        id: buttonMyOrder
    }

    /*Image {
        id: logo
        source: "qrc:/client/resources/rotable_logo.png"

        anchors.bottom: categoryBar.top
        anchors.right: parent.right
        anchors.margins: 10

        width: 250
        fillMode: Image.PreserveAspectFit
    }*/

    CategoryBar {
        id: categoryBar
    }
}
