import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: order

    property int productHeight: Math.max(40,dataView.height * 0.12)
    property int borderWidth: Math.max(8,parent.width * 0.04)
    property int itemSpacing: Math.max(5,dataView.height*0.015)
    property string borderColor: "#46C8CF"

    width: parent.width
    height: orderItemsView.count * productHeight + 6 * borderWidth + (orderItemsView.count-1) * itemSpacing

    border.width: borderWidth
    border.color: borderColor
    radius: width / 12

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
        height: borderWidth + 1
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: orderTime
            text: "00:00"
            color: borderColor
            font.pixelSize: borderWidth * 0.9
            font.bold: true
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
