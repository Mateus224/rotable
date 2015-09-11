import QtQuick 2.3

ListView {

    //anchors.fill: parent
    spacing: 5
    model: orderboard
    id: board
    //width: parent.width - 10; height: parent.height - 35

    visible: count == 0 ? false : true

    //anchors.top: parent.top
    //anchors.topMargin: 10
    delegate:Rectangle{

        width: parent.width - 20
        height: 100
        anchors.centerIn: parent
        color: 'green'
        radius: 8

        Text {
            id : orderLabel
            anchors.centerIn: parent
            text: "Order id: " + orderId

        }

        ListView {
            width: parent.width;
            spacing: 5
            model: orderItems
            anchors.top: orderLabel.bottom
            anchors.topMargin: 10
            id: items
            delegate:Rectangle{

                anchors.top: parent.top
                width: parent.width
                anchors.centerIn: parent

                radius: 8
                Text {
                    anchors.centerIn: parent
                    text: "Order item"//"Order item id: " + id + " name: " + productList.productName(id)
                }
            }
        }
    }

}


