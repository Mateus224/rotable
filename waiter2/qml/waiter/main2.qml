import QtQuick 2.1
import QtQuick.Layouts 1.1

RowLayout {
    id: mainScreen
    anchors.fill: parent
    spacing: 6

    signal sendToBoardOrder(int id)

    Column {
        id: sidebar

        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.minimumWidth: 200
        Layout.maximumWidth: 300
        Layout.minimumHeight: 150

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
                        anchors.centerIn: parent
                        text: "Table: " + name + ", " + id
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

        ListView {
            width: 100; height: 100
            spacing: 5

            model: orderboard
            delegate: Text { text: "Order id: " + id }
        }
    }

}

