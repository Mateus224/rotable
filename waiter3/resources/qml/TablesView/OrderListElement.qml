import QtQuick 2.5

Rectangle{
    id: order

    property int productHeight: Math.max(40,dataView.height * 0.08)
    property int borderWidth: Math.max(4,orderList.width * 0.02)
    property int listWidth: Math.max(100,orderList.width)
    property int itemSpacing: Math.max(10,dataView.height*0.02)
    property string borderColor: "#46C8CF"
    property int listHeight: orderItemsView.count * productHeight + 6 * borderWidth + (orderItemsView.count-1) * itemSpacing

    property string orderTag
    property bool caught: false
    property point beginDrag: Qt.point(x,y)

    width: listWidth
    height: model.itemCount > 0 ? listHeight : 0

    border.width: borderWidth
    border.color: borderColor
    radius: width / 12

    Drag.active: dragArea.drag.active

    z: (dragArea.pressed || dragArea.drag.active) ? 1 : 0

    MouseArea{
        id:dragArea

        anchors.fill: parent
        drag.target: parent

        onPressed: {
            order.beginDrag = Qt.point(order.x, order.y);
//            console.log("Order tag: "+orderTag);
            if ( orderTag == "New" ) {
                orderList.z = 1
                outgoingList.z = 0
                orderList.clip = false
            }
            else {
                orderList.z = 0
                outgoingList.z = 1
                outgoingList.clip = false
            }
        }
        onReleased: {
            if(!order.caught) {
                backAnimX.from = order.x;
                backAnimX.to = beginDrag.x;
                backAnimY.from = order.y;
                backAnimY.to = beginDrag.y;
                seq.start()
            }
            else {
                readyOrder;
                if ( orderTag == "New" ) orderboard.changeState(3)
                else orderboard.changeState(0)
            }
        }
    }
    SequentialAnimation {
        id:seq

        ParallelAnimation {
            id: backAnim
            SpringAnimation { id: backAnimX; target: order; property: "x"; duration: 300; spring: 2; damping: 0.2 }
            SpringAnimation { id: backAnimY; target: order; property: "y"; duration: 300; spring: 2; damping: 0.2 }
        }

        ScriptAction {
            script: {
                if ( orderTag == "New" ) orderList.clip = true
                else outgoingList.clip = true
                orderList.z = outgoingList.z = 0
            }
        }

    }

    ListView{
        id: orderItemsView

        anchors.margins: borderWidth*1.5
        anchors.topMargin: borderWidth*3
        anchors.bottomMargin: borderWidth*3
        anchors.fill: parent

        z: parent.z

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

        z: parent.z

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
