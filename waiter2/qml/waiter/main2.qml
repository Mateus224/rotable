import QtQuick 2.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.3
import QtGraphicalEffects 1.0

ApplicationWindow {
    id:applicationWindow
    visible: true
    //visibility: "FullScreen"
    title: qsTr("Waiter client")
    color: "#7AAEEE"
    property int margin: 10

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
                clip: true
                Layout.minimumWidth: 100
                spacing: margin
                header: bannercomponent
                footer: Rectangle {
                    width: parent.width; height: 50;
                    gradient: clubcolors2
                }
                ExclusiveGroup {
                    id: tableExclusiveGroup
                }

                model: tables

                delegate: Button{
                    id: tableListButton
                    style: ButtonStyle {
                        background: Rectangle {
                            implicitWidth: 100
                            implicitHeight: 70
                            border.width: control.activeFocus ? 2 : 1
                            border.color: "white"
                            radius: 10
                            gradient: Gradient {
                                GradientStop { position: 0 ; color: control.pressed ? "#800000FF" : "#8EE2FE" }
                                GradientStop { position: 1 ; color: control.pressed ? "#8EE2FE" : "#800000FF" }
                            }
                        }
                    }
                    enabled: model.orderNumber === 0 ? false : true

                    width:  parent.width
                    checkable: true
                    exclusiveGroup: tableExclusiveGroup
                    property var connected: model.isConnected ? "Connected" : "Disconnected"
                    Text{
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: "Lobster two"
                        text:model.name + "\n" + "Orders: " + model.orderNumber + "\n" + connected
                    }
                    onClicked: tables.sendToBoardOrder(model.id)
                }
            }
            Component {     //instantiated when header is processed
                id: bannercomponent
                Rectangle {
                    id: banner
                    width: parent.width; height: 60
                    gradient: clubcolors
                    border {
                        color: "#7AAEEE"//"#9EDDF2";
                        width: 2}
                    Text {
                        font.family: "Lobster two"
                        anchors.centerIn: parent
                        text: "Tables"
                        font.pixelSize: 22
                        font.bold: true
                    }
                }
            }
            Gradient {
                id: clubcolors
                GradientStop { position: 0.0; color:"#8EE2FE" }//"#8EE2FE"}
                GradientStop { position: 0.66; color: "#7AAEEE"}
            }
            Gradient {
                id: clubcolors2
                GradientStop { position: 0.0; color:"#7AAEEE" }//"#8EE2FE"}
                GradientStop { position: 0.66   ; color: "#8EE2FE"}
            }

            Text{
                id: labelneedList
                text: qsTr("Table need waiter")
                font.bold: true
                font.family: "Lobster two"
                font.pixelSize: 20
                anchors.top: tableList.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }

            ListView {
                id: needList
                y: 500 //300
                height: 10
                anchors.top: labelneedList.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.leftMargin: 0
                Layout.fillHeight: true
                Layout.minimumWidth: 100
                spacing: margin

                model: needBoard

                delegate: Button{
                    id: needBoardButton
                    width:  parent.width
                    text: "Table: " + model.tableName
                    style: ButtonStyle {
                        background: Rectangle {
                            implicitWidth: 100
                            implicitHeight: 25
                            border.width: control.activeFocus ? 2 : 1
                            border.color: "white"
                            radius: 5
                            gradient: Gradient {
                                GradientStop { position: 0.00 ; color: control.pressed ? "RED" : "#8EE2FE" }
                                GradientStop { position: 0.90 ; color: control.pressed ? "#8EE2FE" : "RED" }
                            }
                        }
                    }
                    onClicked: needBoard.unneedTable(model.tableIdx)
                }
            }

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
                ListView {
                    anchors.topMargin: 10
                    //anchors.top: text1.bottom
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    //anchors.fill: parent
                    spacing: 5
                    model: orderboard
                    id: board
                    //anchors.fill: parent
                    Layout.minimumHeight: 200
                    //Layout.fillWidth: true
                    Layout.fillHeight: true
                    header:bannerO
                    footer: Rectangle {
                        width: parent.width; height: 50;
                        gradient: clubcolors2
                    }

                    Component{
                        id: order
                        ColumnLayout{
                            anchors.horizontalCenter: parent.horizontalCenter
                            //                            width: parent.width

                            spacing: 10
                           /* Label {
                                id: labelOrder
                                text: String(model.orderId)
                            }*/
                            ListView{
                                id: orderItemsView
                                height: 100 // depending on the number of the orders <----------------------TODO-----
                                //Layout.fillHeight: true

                                model: orderItems
                                delegate: CheckBox{
                                    id: changeCheck
                                    width: 200

                                    Layout.fillWidth: true
                                    text: productList.productName(model.modelData.productId) +"   " + model.modelData.amount +"x"
                                    onClicked: model.modelData.change = checked
                                    Component.onCompleted: checked = model.modelData.change
                                    style: CheckBoxStyle {
                                        background:
                                            Rectangle{
                                            //width: parent.width
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
                Component {     //instantiated when header is processed
                    id: bannerO
                    Rectangle {
                        id: banner
                        width: parent.width; height: 60
                        gradient: clubcolors
                        border {
                            color: "#7AAEEE"//"#9EDDF2";
                            width: 2}
                        Text {
                            font.family: "Lobster two"
                            anchors.centerIn: parent
                            text: qsTr("Bill on table: ") + orderboard.ordersPrice.toFixed(2)
                            font.pixelSize: 22
                            font.bold: true
                        }
                    }
                }
            //}
        }
    }
}
