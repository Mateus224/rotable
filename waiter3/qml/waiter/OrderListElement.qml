import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: order

    property int productHeight: Math.max(40,dataView.height * 0.08)
    property int borderWidth: Math.max(4,parent.width * 0.02)
    property int listWidth: Math.max(100,parent.width)
    property int itemSpacing: Math.max(10,dataView.height*0.02)
    property string borderColor: "#46C8CF"
    property int listHeight: orderItemsView.count * productHeight + 6 * borderWidth + (orderItemsView.count-1) * itemSpacing

    width: listWidth
    height: model.itemCount > 0 ? listHeight : 0

    border.width: borderWidth
    border.color: borderColor
    radius: width / 12

    visible: model.itemCount > 0

    ListView{
        id: orderItemsView

        anchors.margins: borderWidth*1.5
        anchors.topMargin: borderWidth*3
        anchors.bottomMargin: borderWidth*3
        anchors.fill: parent

        spacing: itemSpacing

        model: orderItems
        delegate: OrderProductListElement { height: productHeight}
    }

    Rectangle {
        width: orderTime.font.pixelSize * 4
        height: borderWidth * 2
        anchors.top: parent.top
        anchors.topMargin: -1
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: orderTime
            text: model.timeSent
            color: borderColor
            font.pixelSize: borderWidth * 1.2
            font.bold: true
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
