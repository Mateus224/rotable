import QtQuick 2.0
import ".."

Rectangle {
    anchors.fill: parent
    color: "#00000000"

    MyOrderButton {
        id: buttonMyOrder
    }

    Rectangle {
        anchors.fill: parent
        anchors.topMargin: parent.height * 0.2
        anchors.leftMargin: parent.width * (1.0 - 0.805) / 2.0
        anchors.rightMargin: parent.width * (1.0 - 0.805) / 2.0
        anchors.bottomMargin: parent.height * (0.09125 + 0.10 + 0.125)

        color: "#3f494a"

        Rectangle {
            anchors.fill: parent
            anchors.margins: parent.height * 0.02

            color: "#000000"
        }
    }

    CategoryBar {
        id: categoryBar
    }
}

