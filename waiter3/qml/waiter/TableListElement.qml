import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {

    id: buttonBody

    enabled: model.orderNumber == 0 ? false : true

    width: parent.width

    property var connected: model.isConnected ? "Connected" : "Disconnected"

    anchors.horizontalCenter: parent.horizontalCenter
    color: model.isSelected ? "#000FDF" : "#FFFFFF"

    Text {
        id: tableName
        anchors.centerIn: parent
        text: qsTr("Table ") + model.name + langObject.emptyString
        font.pixelSize: parent.height * 0.3
        color: model.isSelected ? "#FFFFFF" : "#000000"
    }

    Rectangle {
        id: newOrderCircle

        //visible: !model.isSelected
        visible: false
        height: parent.height * 0.5
        width: height
        radius: height
        color: "#FF3F3F"
        anchors.left: tableName.right
        anchors.leftMargin: parent.width * 0.02
        anchors.verticalCenter: parent.verticalCenter
    }

    Text {
        id: selectedArrow

        visible: model.isSelected

        anchors.right: parent.right
        anchors.rightMargin: parent.width * 0.02
        anchors.verticalCenter: parent.verticalCenter

        text: ">"
        font.bold: true
        font.pixelSize: parent.height * 0.4
        color: "#FFFFFF"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: tables.sendToBoardOrder(model.id)
    }
}
