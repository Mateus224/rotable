import QtQuick 2.3
import QtQuick.Layouts 1.1

RowLayout {
    id: mainScreen
    anchors.fill: parent
    spacing: 10

    signal sendToBoardOrder(int id)

    Column {
        id: sidebar

        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.minimumWidth: 200
        Layout.maximumWidth: 300
        Layout.minimumHeight: 150

        anchors.left: parent.left
        anchors.leftMargin: 10

        spacing: 5

        Rectangle {
            Text {
                anchors.centerIn: parent
                text: 'Menu'
            }
            radius: 10.0
            width: parent.width - 10; height: 30
        }

        Rectangle{

            Text{
                anchors.centerIn: parent
                text: "Log out"
            }
            color: "red";
            radius: 10.0
            width: parent.width - 10; height: 50
        }

        Rectangle{

            Text{
                anchors.centerIn: parent
                text: "Exit"
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    Qt.quit()
                }
            }

            color: "red";
            radius: 10.0
            width: parent.width - 10; height: 50
        }

        Rectangle {
            Text {
                anchors.centerIn: parent
                text: 'Tables'
            }
            radius: 10.0
            width: parent.width - 10; height: 30
        }

        Rectangle {
            radius: 10.0
            width: parent.width - 10; height: 100

            ListView {
                id: tableList
                spacing: 5
                width: parent.width;

                model: tables
                delegate: Rectangle {
                    color: "#750a0a"
                    height: 50
                    radius: 10.0
                    width: parent.width
                    Text{
                        //anchors.centerIn: parent
                        text: "Table: " + name + ", " + id + "\nOrders: " + orderNumber
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            mainScreen.sendToBoardOrder(id)
                        }
                    }
                }
            }
        }
    }

    Rectangle {

        color: 'plum'
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.minimumWidth: 500
        Layout.preferredWidth: 800
        Layout.preferredHeight: 100

        border.color: "lightsteelblue"
        border.width: 4
        radius: 8

        Text{
            text: orderboard.count
        }

        ListView {
            width: parent.width; height: parent.height
            spacing: 5
            model: orderboard
            id: board

            //anchors.top: parent.top
            anchors.topMargin: 10
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
    }

}

