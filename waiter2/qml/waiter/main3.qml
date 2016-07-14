import QtQuick 2.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.3

ApplicationWindow {

    visible: true
    title: qsTr("Waiter client")

    property int margin: 10

    width: 650
    height: 400
    minimumWidth: 650
    minimumHeight: 400

    RowLayout{
        id: mainLayout
        spacing: 10

        anchors.margins: margin
        anchors.fill: parent

        ColumnLayout {
            id: menuLayout
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
                id: tableMenuLabel
                text: qsTr("Table list")
                anchors.top: rowBox.bottom
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
                    property var connected: model.isConnected ? "Connected" : "Disconnected"
                    text: "Table: " + model.name + ", " + model.id + "\nOrders: " + model.orderNumber + "\n" + connected

                    onClicked: tables.sendToBoardOrder(model.id)
                }
            }
            //}
            //  }


        }
        ColumnLayout{
            id: orderLayout
            anchors.left: menuLayout.right
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top

            //Layout.fillWidth: true

            spacing: margin


            RowLayout{
                id: orderButton

                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                spacing: margin
                Button{
                    text: "To Pay"
                    enabled: orderboard.isSomethingSelected
                    onClicked:{
                        orderboard.changeState(3);
                    }
                }
                Button{
                    text: "Payed"
                    enabled: orderboard.isSomethingSelected
                    onClicked:{
                        orderboard.changeState(1);
                    }
                }
                Button{
                    text: "Remove"
                    enabled: orderboard.isSomethingSelected
                    onClicked:{
                        orderboard.changeState(2);
                    }
                }

            }

            Text {
                id: text1
                text: qsTr("Bill on table: ") + orderboard.ordersPrice.toFixed(2)
                Layout.fillHeight: false
                Layout.fillWidth: true
                font.pixelSize: 12
            }

            ScrollView {
                Layout.fillWidth: false
                Layout.fillHeight: false
                transformOrigin: Item.Center
                anchors.topMargin: 10
                anchors.top: text1.bottom
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.leftMargin: 0
                horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOn
                ListView {

                    //anchors.fill: parent
                    spacing: 5
                    model: orderboard
                    id: board
                    //anchors.fill: parent
                    Layout.minimumHeight: 200
                    //Layout.fillWidth: true
                    Layout.fillHeight: true

                    Component{
                        id: order
                        ColumnLayout{

                            //                            width: parent.width

                            spacing: 5
                            Label {
                                id: labelOrder
                                text: String(model.orderId)
                            }
                            ListView{
                                id: orderItemsView
                                height: 50
                                //Layout.fillHeight: true

                                model: orderItems
                                delegate: CheckBox{
                                    id: changeCheck

                                    Layout.fillWidth: true
                                    text: productList.productName(model.modelData.productId)  + " Amount: " + model.modelData.amount
                                    onClicked: model.modelData.change = checked
                                    checked: model.modelData.change
//                                    Component.onCompleted: checked = model.modelData.change
                                    //                                    Connections {
                                    //                                        target: model.modelData
                                    //                                        onChangeChange: changeCheck.checked = model.modelData.change
                                    //                                    }
                                    //                                    onCheckedChanged: {
                                    //                                       model.modelData.readyToChange(checked)
                                    //                                    }
                                    //                                    checked: model.modelData.change
                                    style: CheckBoxStyle {
                                        background:
                                            Rectangle{
                                            color: {
                                                switch(model.modelData.state)
                                                {
                                                case 0: "Green"; break;
                                                case 1: "Blue"; break;
                                                case 2: "Gray"; break;
                                                case 3: "Red"; break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            Label{
                                text: qsTr("To pay: ") + orderPrice;
                            }
                            Button{
                                id: buttonOrder
                                text: qsTr("Select all")
                                onClicked: model.prepareOrderToChange

                            }
                        }
                    }
                    delegate:order
                }
                Label{
                    id: labelneedList
                    text: qsTr("Table need waiter")
                    anchors.top: tableList.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                ListView {
                    id: needList
                    y: 300
                    height: 200
                    anchors.top: labelneedList.bottom
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.leftMargin: 0
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
}
