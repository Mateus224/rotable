import QtQuick 2.3

Item{
    Rectangle {
        color: orderNumber == 0  ? "gray" : "green"
        height: 50
        radius: 10.0
        width: parent.width
        Text{
            anchors.fill: parent
            anchors.leftMargin: 15
            anchors.topMargin: 5
            text: "Table: " + name + ", " + id + "\nOrders: " + orderNumber
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                //mainScreen.sendToBoardOrder(id)
            }
        }
    }
}
