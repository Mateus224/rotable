import QtQuick 2.5

Rectangle {

    id: buttonBody

    //enabled: model.orderNumber == 0 ? false : true

    width: parent.width

//    property bool connected: model.isConnected ? true : false

    anchors.horizontalCenter: parent.horizontalCenter
    color: model.isSelected ? waiterMain.menuColor : "#FFFFFF"

    Text {
        id: tableName
        anchors.centerIn: parent
        text: qsTr("Table ") + model.name + langObject.emptyString
        font.pixelSize: parent.height * 0.4
        color: model.isConnected ? (model.isSelected ? "#FFFFFF" : "#000000") : "#8F8F8F"
    }

    Rectangle {
        id: newOrderCircle

        visible: model.incomingCount > 0
        height: parent.height * 0.4
        width: height
        radius: height
        color: "#FF3F3F"
        anchors.right: selectedArrow.left
        anchors.rightMargin: parent.width * 0.02
        anchors.verticalCenter: parent.verticalCenter

        Text {
            id: number
            anchors.centerIn: parent
            text: model.incomingCount
            color: "#FFFFFF"
            font.pixelSize: parent.height * 0.6
        }
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
