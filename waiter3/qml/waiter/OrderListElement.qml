import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: order

    property int productHeight: Math.max(30,dataView.height * 0.1)
    property int borderWidth: Math.max(8,parent.width * 0.04)
    property int itemSpacing: Math.max(5,dataView.height*0.016)

    width: parent.width
    height: orderItemsView.count * productHeight + 3 * borderWidth + (orderItemsView.count-1) * itemSpacing

    border.width: borderWidth
    border.color: "#46C8CF"
    radius: width / 10

    ListView{
        id: orderItemsView

        anchors.margins: borderWidth*1.5
        anchors.fill: parent

        spacing: itemSpacing

        model: orderItems
        delegate: OrderProductListElement { height: productHeight}
    }
}
