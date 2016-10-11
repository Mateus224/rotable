import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {

    id: bototmBarLayout

    width: parent.width
    height: Math.max(50,parent.height * 0.14)
    anchors.bottom: parent.bottom
    anchors.horizontalCenter: parent.horizontalCenter

    Rectangle {
        id: empty
        width: waiterMain.width * 0.3
        height: parent.height
        anchors.left: parent.left
        anchors.top: parent.top
    }

    Rectangle {
        id: incText

        height: parent.height * 0.5
        width: waiterMain.width * 0.35
        anchors.left: empty.right
        anchors.top: parent.top

        Text {
            text: qsTr("Incoming") + langObject.emptyString
            font.pixelSize: parent.height * 0.8
            anchors.centerIn: parent
        }
    }

    Rectangle {

        height: parent.height * 0.5
        width: waiterMain.width * 0.35
        anchors.left: incText.right
        anchors.top: parent.top

        Text {
            text: qsTr("Outgoing") + langObject.emptyString
            font.pixelSize: parent.height * 0.8
            anchors.centerIn: parent
        }
    }
}
