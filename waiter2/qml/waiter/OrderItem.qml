import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    anchors { fill: parent;}

    Column {
        id: column1
        anchors.fill: parent

        Text {
            id: text1
            text: qsTr("Text")
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 0
            font.pixelSize: 12
        }

        ListView {
            id: orderItemsView
            anchors.top: text1.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.topMargin: -16
            delegate: Item {
                x: 5
                width: 80
                height: 40
                CheckBox{
                    text: productList.productName(model.modelData.productId)  + " Amount: " + model.modelData.amount
                    onClicked: model.modelData.change = checked
                    Component.onCompleted: checked = model.modelData.changee
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
            model: orderItems

        }
    }

}
