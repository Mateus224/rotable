import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

ApplicationWindow {

    visible: true
    title: qsTr("Waiter client")

    property int margin: 10

    width: mainLayout.implicitWidth + 2 * margin
    height: mainLayout.implicitHeight + 2 * margin
    minimumWidth: mainLayout.Layout.minimumWidth + 2 * margin
    minimumHeight: mainLayout.Layout.minimumHeight + 2 * margin

    RowLayout{
        id: mainLayout

        spacing: 10
        anchors.margins: margin
        anchors.fill: parent

        width: menuLayout.implicitWidth + orderLayout.implicitWidth + spacing
        height: Math.max(menuLayout.height, orderLayout.height)
        //minimumWidth: menuLayout.minimumWidth + orderLayout.minimumWidth + spacing
        //minimumHeight: Math.max(menuLayout.minimumHeight, orderLayout.minimumHeight)

        ColumnLayout {
                id: menuLayout

                Layout.fillHeight: true

                anchors.margins: margin

                GroupBox {
                    id: rowBox
                    title: qsTr("Menu")
                    Layout.fillWidth: true

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

//                GroupBox {
//                    id: gridBox
//                    title: qsTr("Table list")
//                    Layout.fillWidth: true
//                    height: {
//                        if(tables.count == 0){
//                            0;
//                        }
//                        else{
//                            tableList.implicitHeight;
//                        }
//                    }

//                    GridLayout {
//                        id: gridLayout
//                        rows: 2
//                        flow: GridLayout.LeftToRight
//                        Layout.fillWidth: true
                        Label{
                            text: qsTr("Table list")
                        }

                        ListView {
                            id: tableList
                            Layout.fillWidth: true
                            //height: implicitHeight
                            //height: tableList.count * (spacing + 50)
                            height:200
                            spacing: margin

                            ExclusiveGroup {
                                id: tableExclusiveGroup
                            }

                            model: tables

                            delegate: Button{
                                id: tableListButton

                                width:  parent.width
                                checkable: true
                                exclusiveGroup: tableExclusiveGroup
                                text: "Table: " + model.name + ", " + model.id + "\nOrders: " + orderNumber

                                onClicked: tables.sendToBoardOrder(model.id)
                            }
                        }
                    //}
              //  }

            }
        ColumnLayout{
            id: orderLayout

            Layout.fillHeight: true
            Layout.fillWidth: true

            Layout.minimumWidth: board.width

            ListView {

                //anchors.fill: parent
                spacing: 5
                model: orderboard
                id: board
                anchors.fill: parent
                width: 200
                //Layout.fillWidth: true

                Component{
                    id: order
                    Label {
                        id: labelOrder
                        text: String(model.id)
                    }
                }

                delegate:order
            }
        }
    }

}


//    Label{
//        id: orderLabel

//        text: qsTr("Orders")

//        height: 50

//        width: parent.width - menu.width
//    }

//    Menu{
//        id: menu

//        Layout.preferredWidth: 150
//        Layout.minimumWidth: 150
//        //Layout.preferredHeight: 100

//        Layout.rowSpan: 2
//    }

//    OrderList{
//        id: orders
//        Layout.rowSpan: 7

//        height: parent.height - orderLabel.height
//        width: parent.width - menu.width
//    }

//    Label{
//        id: tableLabel

//        text: qsTr("Tables")

//        Layout.preferredWidth: 150
//        Layout.minimumWidth: 150

//    }

//    TableList{
//        Layout.preferredWidth: 150
//        Layout.minimumWidth: 150

//        Layout.preferredHeight: 200

//        Layout.column: 0
//        Layout.row: 4


//    }
