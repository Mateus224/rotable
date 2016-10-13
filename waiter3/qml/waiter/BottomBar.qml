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
        width: waiterMain.leftMenuWidth
        height: parent.height
        anchors.left: parent.left
        anchors.top: parent.top
    }

    Rectangle {
        id: incText

        height: parent.height * 0.4
        width: waiterMain.width * 0.33
        anchors.left: empty.right
        anchors.top: parent.top

        Text {
            text: qsTr("Incoming") + langObject.emptyString
            font.pixelSize: parent.height * 0.8
            anchors.centerIn: parent
        }
    }

    Rectangle {

        height: parent.height * 0.4
        width: waiterMain.width * 0.33
        anchors.left: incText.right
        anchors.top: parent.top

        Text {
            text: qsTr("Outgoing") + langObject.emptyString
            font.pixelSize: parent.height * 0.8
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: needsWaiterRect
        height: parent.height * 0.6
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        TableNeedsWaiterList { id: needsWaiterList}
    }
}
