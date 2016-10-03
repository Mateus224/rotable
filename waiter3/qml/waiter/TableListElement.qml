import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {

    id: buttonBody

    enabled: model.orderNumber == 0 ? false : true

    width: parent.width
    height: 50

    property var connected: model.isConnected ? "Connected" : "Disconnected"

    anchors.horizontalCenter: parent.horizontalCenter
    color: model.isSelected ? "#000FDF" : "#FFFFFF"

    Text {
        id: tableName
        anchors.centerIn: parent
        text: qsTr("Table ") + model.name + langObject.emptyString
        font.pixelSize: parent.height * 0.4
    }

    Rectangle {
        id: newOrderCircle

//        visible: model.isSelected
        height: parent.height * 0.6
        width: parent.height * 0.6
        radius: height
        color: "#FF3F3F"
        anchors.left: tableName.right
        anchors.leftMargin: parent.width * 0.01
        anchors.verticalCenter: parent.verticalCenter
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: tables.sendToBoardOrder(model.id)
    }
}
