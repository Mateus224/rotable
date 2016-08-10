import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

ColumnLayout{
    id: orderLayout
    transformOrigin: Item.Center
    spacing: 1
    anchors.left: menuLayout.right
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.top: parent.top
    
    //Layout.fillWidth: true
    
    
    
    RowLayout{
        id: orderButton
        
        width: parent.width
        Layout.fillHeight: true
        Layout.fillWidth: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        spacing: margin
        Button{
            text: "To Pay"
            Layout.fillWidth: true
            enabled: orderboard.isSomethingSelected
            onClicked:{
                orderboard.changeState(3);
            }
        }
        Button{
            text: "Payed"
            Layout.fillWidth: true
            enabled: orderboard.isSomethingSelected
            onClicked:{
                orderboard.changeState(1);
            }
        }
        Button{
            text: "Remove"
            Layout.fillWidth: true
            enabled: orderboard.isSomethingSelected
            onClicked:{
                orderboard.changeState(2);
            }
        }
        
    }
    
    Text {
        id: text1
        text: qsTr("Bill on table: ") + orderboard.ordersPrice.toFixed(2)
        Layout.fillHeight: true
        Layout.fillWidth: true
        font.pixelSize: 12
    }
    
    ListView {

        //anchors.fill: parent
        spacing: 5
        model: orderboard
        id: board
        Layout.fillWidth: true
        highlightRangeMode: ListView.NoHighlightRange
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

    NeedList {
        id: needList
        Layout.fillWidth: true
        Layout.fillHeight: true
    }




}
