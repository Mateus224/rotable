import QtQuick 2.2
import QtQuick.Controls 1.3
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
                    //Layout.fillWidth: true

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
                            Layout.fillHeight: true
                            //height: implicitHeight
                            //height: tableList.count * (spacing + 50)
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
                                text: "Table: " + model.name + ", " + model.id + "\nOrders: " + model.orderNumber

                                onClicked: tables.sendToBoardOrder(model.id)
                            }
                        }
                    //}
              //  }

            }
        ColumnLayout{
            id: orderLayout

            //Layout.fillWidth: true

            spacing: margin


            RowLayout{
                height: 100
                width: parent.width
                spacing: margin
                Button{
                    text: "Payed"
                    enabled: false
                }
                Button{
                    text: "Remove"
                    enabled: false
                }
                Button{
                    text: "Something else"
                    enabled: false
                }

            }

            ScrollView {
                //horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOn
                ListView {

                    //anchors.fill: parent
                    spacing: 5
                    model: orderboard
                    id: board
                    //anchors.fill: parent
                    Layout.minimumHeight: 200
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Component{
                        id: order
                        Grid{
                            columns: 2
                            rows: 2
                            flow: GridLayout.LeftToRight
                            width: parent.width
                            columnSpacing: width - labelOrder.width - buttonOrder.width
                            height: 50
                            Label {
                                id: labelOrder
                                text: String(model.orderId)
                            }
                            Button{
                               id: buttonOrder
                               text: qsTr("Select all")

                            }
                            ListView{
                                height: 50
                                model: orderItems
                                delegate: CheckBox{
                                    Layout.columnSpan: 2
                                    text: productList.productName(model.modelData.id)  + " Amount: " + model.modelData.amount
                                }
                            }
                        }
                    }

                    delegate:order
                }

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
