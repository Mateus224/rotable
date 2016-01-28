import QtQuick 2.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.3

Rectangle{
    color: "#7AAEEE"
    //anchors.fill: parent
    ColumnLayout{
        id: menuLayout_
        anchors.bottomMargin: 0
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.topMargin: 0
        spacing: 10

        Layout.fillHeight: true

        anchors.margins: margin

        GroupBox {
            id: rowBox
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            title: qsTr("Menu")
            //Layout.fillWidth: true

            RowLayout {
                id: rowLayout
                //anchors.fill: parent
                Button {
                    text: qsTr("Log out")
                    enabled: false
                }
                Button {
                    text: qsTr("Settings")
                    enabled: false
                }
                Button {
                    text: qsTr("Exit")
                    onClicked: Qt.quit()
                }
            }

            Label{
                id: tableMenuLabel
                text: qsTr("Table list")
                //anchors.top: rowBox.bottom
                anchors.topMargin: 0
                anchors.horizontalCenter: parent.horizontalCenter
            }

            ListView {
                id: tableList
                height: 200
                anchors.top: tableMenuLabel.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.leftMargin: 0
                Layout.fillHeight: true
                Layout.minimumWidth: 200
                spacing: margin

                ExclusiveGroup {
                    id: tableExclusiveGroup
                }

                model: tables

                delegate: Button{
                    id: tableListButton

                    enabled: model.orderNumber == 0 ? false : true

                    width:  parent.width
                    checkable: true
                    exclusiveGroup: tableExclusiveGroup
                    property var connected: model.isConnected ? "Connected" : "Disconnected"
                    text: "Table: " + model.name + ", " + model.id + "\nOrders: " + model.orderNumber + "\n" + connected

                    onClicked: tables.sendToBoardOrder(model.id)
                }
            }
            //}
            //  }
            Label{
                id: labelneedList
                text: qsTr("Table need waiter")
                //anchors.top: tableList.bottom
                //anchors.horizontalCenter: parent.horizontalCenter
            }

            ListView {
                id: needList
                y: 300
                height: 200
                //anchors.top: labelneedList.bottom
                //anchors.right: parent.right
                //anchors.left: parent.left
                //anchors.leftMargin: 0
                Layout.fillHeight: true
                //height: implicitHeight
                //height: tableList.count * (spacing + 50)
                Layout.minimumWidth: 200
                spacing: margin

                model: needBoard

                delegate: Button{
                    id: needBoardButton
                    width:  parent.width
                    text: "Table " + model.tableName

                    onClicked: needBoard.unneedTable(model.tableIdx)
                }
            }
        }
    }
}
