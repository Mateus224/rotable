import QtQuick 2.1
import QtQuick.Layouts 1.1

RowLayout {
    id: mainScreen
    anchors.fill: parent
    spacing: 6

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
                width: 100; height: 100
                spacing: 5

                model: tables
                delegate: Rectangle {
                    height: 25
                    width: 100
                    color: "blue"
                    Text { text: "Table name: " + name }
                    Text { text: "Table id: " + id }
                }
            }
        }

        Rectangle {
            Text {
                anchors.centerIn: parent
                text: 'End menu'
            }
            radius: 10.0
            width: parent.width - 10; height: 30
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

        Text {
            anchors.centerIn: parent
            text: 'Orders'
        }
    }

}

