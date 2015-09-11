import QtQuick 2.3

Rectangle {
    radius: 10.0
    width: parent.width - 10; height: parent.height

    ListView {
        id: tableList
        spacing: 5
        width: parent.width;
        height: parent.height

        model: tables
        delegate: Rectangle {
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
}

