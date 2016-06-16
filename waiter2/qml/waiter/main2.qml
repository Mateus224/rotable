import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.3
import QtGraphicalEffects 1.0

ApplicationWindow {
    id:applicationWindow
    visible: true
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

            Rectangle{
                id: incomeText
                anchors.top: parent.bottom
                anchors.bottom: parent.bottom
                anchors.bottomMargin: parent.height/5.5
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.leftMargin: 0
                gradient: clubcolors
                border {
                    color: "#7AAEEE"//"#9EDDF2";
                    width: 2}
                Text {
                    id: incomeTextLabel
                    font.family: "Lobster two"
                    height: 75
                    anchors.top: parent.top
                    anchors.centerIn: parent
                    text: qsTr("Today income")
                    font.pixelSize: 22
                    font.bold: true
                }
                Text {
                    font.family: "Lobster two"
                    //anchors.left: parent.left
                    anchors.top: incomeTextLabel.bottom
                    anchors.centerIn: parent
                    text: tables.incomeStr
                    font.pixelSize: 22
                    font.bold: true
                }
            }

            ListView {
                id: tableList
                z:1
                height: (applicationWindow.height/4)*3
                anchors.top: rowBox.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.leftMargin: 0
                Layout.fillHeight: true
                clip: true
                Layout.minimumWidth: 100
                spacing: margin
                header: bannercomponent
                footer: Rectangle {
                    z:1
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
                            implicitHeight: 50
                            border.width: control.activeFocus ? 2 : 1
                            border.color: "white"
                            property var  gradientSelect: Gradient {
                                GradientStop { position: 0.00 ; color: control.pressed ? "RED" : "#8EE2FE" }
                                GradientStop { position: 0.90 ; color: control.pressed ? "#8EE2FE" : "RED" }
                            }

                            property var gradientNotSelect: Gradient {
                                GradientStop { position: 0 ; color: "#8EE2FE" }
                                GradientStop { position: 1 ; color: "#800000FF" }
                            }

                            radius: 10
                            gradient: model.isChange ? gradientSelect : gradientNotSelect
                        }
                    }

                    enabled: model.orderNumber === 0 ? false : true
                    width:  2*parent.width/3
                    checkable: true
                    exclusiveGroup: tableExclusiveGroup
                    property var connected: model.isConnected ? "Connected" : "Disconnected"
                    Text{
                        font.pixelSize: parent.height * 0.25
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: "Lobster two"
                        text:"Table: "+model.name + "\n" + "Orders: " + model.orderNumber + "\n" + connected
                    }
                    onClicked: {
                        tables.sendToBoardOrder(model.id)
                    }

                }
            }
            Component {     //instantiated when header is processed
                id: bannercomponent
                Rectangle {
                    id: banner
                    width: parent.width;
                    height: 60
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

        }

        ColumnLayout{
            z:0
            id: orderLayout
            anchors.left: menuLayout.right
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top

            //Layout.fillWidth: true

            spacing: margin


            RowLayout{
                id: orderButton
                z:0
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
            //------------------------------------------------------------
            Rectangle{
                id: billOnTableText
                anchors.topMargin: parent.height/5
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 2*parent.height/3
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.leftMargin: 0
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


                ListView {
                    id: board
                    z:0
                    anchors.top: billOnTableText.bottom
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height/4
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    spacing: 5
                    model: orderboard

                    //Layout.minimumHeight: 200
                    Layout.fillHeight: true
                    //height: 250
                    //header:bannerO
                    orientation: ListView.Horizontal
                    /*footer: Rectangle {
                        width: 300; height: 50;
                        gradient: clubcolors2
                    }*/


                    Component{
                        id: order

                        ColumnLayout{
                            //anchors.horizontalCenter: parent.horizontalCenter
                            //
                            z:0
                            width: 150
                           /* Label {
                                id: labelOrder
                                text: String(model.orderId)
                            }*/
                            Label{
                                z:0
                                font.bold: true
                                font.family: "Lobster two"
                                font.pixelSize: 20
                                text: qsTr("To pay: ") + orderPrice;
                            }

                            ListView{
                                z:0
                                //orientation: ListView.Horizontal
                                id: orderItemsView
                                height: 50 // depending on the number of the orders <----------------------TODO-----
                                //Layout.fillHeight: true
                                Layout.minimumHeight: 200
                                Layout.fillHeight: true
                                /*footer: Rectangle {
                                    width: 150; height: 50
                                    gradient: clubcolors2
                                }*/
                                model: orderItems
                                delegate:
                                    CheckBox{
                                    id: changeCheck
                                    width: 150

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

                            /*Button{
                                id: buttonOrder
                                text: qsTr("Select all")
                                onClicked: model.prepareOrderToChange

                            }*/
                        }
                    }
                    delegate:order
                }
                Component {     //instantiated when header is processed
                    id: bannerO
                    Rectangle {
                        id: banner
                        width: 300
                        height: 60
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

                Rectangle{
                    id: needWaiterText
                    anchors.top: parent.bottom
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height/5.5
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    gradient: clubcolors
                    border {
                        color: "#7AAEEE"//"#9EDDF2";
                        width: 2}
                    Text {
                        font.family: "Lobster two"
                        //anchors.left: parent.left
                        anchors.centerIn: parent
                        text: qsTr("Table need waiter")
                        font.pixelSize: 22
                        font.bold: true
                    }
                }

                ListView {
                    z:1
                    id: needList
                    //height:applicationWindow.height/5
                    anchors.top: needWaiterText.bottom
                     anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    //Layout.minimumWidth: 100
                    spacing: margin
                    //header: banner_tableNeedWaiter
                    orientation: ListView.Horizontal

                    model: needBoard
                    Component {     //instantiated when header is processed
                        id: banner_tableNeedWaiter
                        Rectangle {
                            id: banner
                            width: 150;
                            height: 60
                            gradient: clubcolors
                            border {
                                color: "#7AAEEE"//"#9EDDF2";
                                width: 2}

                            Text{
                                id: labelneedList
                                text: qsTr("Table need waiter")
                                font.bold: true
                                font.family: "Lobster two"
                                font.pixelSize: 20
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                    }
                    delegate: Button{
                        id: needBoardButton
                        width:  150
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
            //}
        }
    }
}
