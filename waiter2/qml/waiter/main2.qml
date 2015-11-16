import QtQuick 2.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4

ApplicationWindow {

    visible: true
    title: qsTr("Waiter client")

    property int margin: 10

    GridLayout{
        id: mainLayout
        anchors.fill: parent
        columns: 2
        anchors.margins: margin

        ColumnLayout {
                id: menuLayout
                anchors.margins: margin

                GroupBox {
                    id: rowBox
                    title: qsTr("Menu")

                    RowLayout {
                        id: rowLayout
                        anchors.fill: parent
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
                }

                Label{
                    text: qsTr("Table list")
                }

                ListView {
                    id: tableList
                    Layout.fillHeight: true
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
            }
        ColumnLayout{
            id: orderLayout
            spacing: margin

            RowLayout{
                spacing: margin
                Button{
                    text: qsTr("Payed")
                    enabled: orderboard.isSomethingSelected
                    onClicked:{
                        orderboard.changeState(1);
                    }
                }
                Button{
                    text: qsTr("Remove")
                    enabled: orderboard.isSomethingSelected
                    onClicked:{
                        orderboard.changeState(2);
                    }
                }
                Button{
                    text: qsTr("Something else")
                    enabled: orderboard.isSomethingSelected
                    onClicked:{
                        orderboard.changeState(3);
                    }
                }

            }

            ScrollView {
                ListView {
                    spacing: 5
                    model: orderboard
                    id: board

                    delegate:OrderItem
                }

            }

        }
    }

}
