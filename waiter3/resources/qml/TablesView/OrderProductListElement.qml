import QtQuick 2.5

Rectangle {
    id: productButton

    property int borderWidth: Math.max(2,parent.width * 0.01)
    property int itemWidth: Math.max(parent.width*0.7,70)

    width: itemWidth
    anchors.horizontalCenter: parent.horizontalCenter
    radius: width/8

    border.width: borderWidth
    border.color: "#6464FE"

    Text {
        text: productList.productName(model.modelData.productId)  + " x " + model.modelData.amount
        anchors.centerIn: parent
        font.pixelSize: parent.height * 0.4
    }
}
