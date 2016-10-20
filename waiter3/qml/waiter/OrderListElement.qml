import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: order

    property int productHeight: Math.max(40,dataView.height * 0.08)
    property int borderWidth: Math.max(4,orderList.width * 0.02)
    property int listWidth: Math.max(100,orderList.width)
    property int itemSpacing: Math.max(10,dataView.height*0.02)
    property string borderColor: "#46C8CF"
    property int listHeight: orderItemsView.count * productHeight + 6 * borderWidth + (orderItemsView.count-1) * itemSpacing

    property bool caught: false
    property point beginDrag: Qt.point(x,y)

    width: listWidth
    height: model.itemCount > 0 ? listHeight : 0
//    visible: model.itemCount > 0 //temporary fix to prevent empty orders
    visible: model.orderStatus == 0

    border.width: borderWidth
    border.color: borderColor
    radius: width / 12

    Drag.active: dragArea.drag.active

    z: dragArea.drag.active ||  dragArea.pressed ? 2 : 1

    MouseArea{
        id:dragArea

        anchors.fill: parent
        drag.target: parent

        onPressed: {
            order.beginDrag = Qt.point(order.x, order.y);
            console.log("x: "+order.x+" y: "+order.y);
        }
        onReleased: {
            if(!order.caught) {
                backAnimX.from = order.x;
                backAnimX.to = beginDrag.x;
                backAnimY.from = order.y;
                backAnimY.to = beginDrag.y;
                backAnim.start()
            }
            else {
                prepareOrderToChange()
                orderboard.changeState(3);
                console.log("new state: "+model.orderStatus)
            }
        }
    }

    ParallelAnimation {
        id: backAnim
        SpringAnimation { id: backAnimX; target: order; property: "x"; duration: 500; spring: 2; damping: 0.2 }
        SpringAnimation { id: backAnimY; target: order; property: "y"; duration: 500; spring: 2; damping: 0.2 }
    }

    ListView{
        id: orderItemsView

        anchors.margins: borderWidth*1.5
        anchors.topMargin: borderWidth*3
        anchors.bottomMargin: borderWidth*3
        anchors.fill: parent

        interactive: false

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
