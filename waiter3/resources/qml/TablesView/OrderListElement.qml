import QtQuick 2.5

Rectangle{
    id: order

    property int productHeight: Math.max(40,dataView.height * 0.08)
    property int borderWidth: Math.max(4,orderList.width * 0.013)
    property int listWidth: Math.max(100,orderList.width)
    property int itemSpacing: Math.max(10,dataView.height*0.02)
    property string borderColor
    property int listHeight: orderItemsView.count * productHeight + 6 * borderWidth + (orderItemsView.count-1) * itemSpacing

    property string orderTag
    property string targetTag
    property bool caught: false
    property point beginDrag: Qt.point(x,y)

    property var globalPosThis
    property var globalPosNew : waiterMain.mapFromItem(orderList, 0, 0)
    property var globalPosToPay : waiterMain.mapFromItem(outgoingList, 0, 0)
    property var globalPosRemove : waiterMain.mapFromItem(trashImage, 0, 0)
    property var globalPosPayed : waiterMain.mapFromItem(moneyImage, 0, 0)

    width: listWidth
    height: model.itemCount > 0 ? listHeight : 0

    border.width: borderWidth
    border.color: borderColor
    radius: width / 15

    Drag.active: dragArea.drag.active

    z: (dragArea.pressed || dragArea.drag.active) ? 1 : 0

    function isInside(objectPos,targetPos,targetWidth,targetHeight)
    {
        return ( objectPos.x >= targetPos.x && objectPos.x <= targetPos.x+targetWidth
                && objectPos.y >= targetPos.y && objectPos.y <= targetPos.y+targetHeight )
    }
    function handleDragging()
    {
        globalPosThis = waiterMain.mapFromItem(order, 0, 0)
        globalPosThis.x = globalPosThis.x + order.width * 0.95
        if (isInside(globalPosThis,globalPosNew,orderList.width,orderList.height))
            order.borderColor = waiterMain.incomingColor
        else if (isInside(globalPosThis,globalPosToPay,outgoingList.width,outgoingList.height))
            order.borderColor = waiterMain.menuColor
        else if (isInside(globalPosThis,globalPosRemove,trashImage.width,trashImage.height))
            order.borderColor = waiterMain.removeColor
        else if (isInside(globalPosThis,globalPosPayed,moneyImage.width,moneyImage.height))
            order.borderColor = waiterMain.payedColor
        else order.borderColor = orderTag=="New" ? waiterMain.incomingColor : waiterMain.menuColor
    }

    onXChanged: {
        if (dragArea.drag.active) {
            handleDragging()
        }
    }
    onYChanged: {
        if (dragArea.drag.active) {
            handleDragging()
        }
    }

    MouseArea{
        id:dragArea

        anchors.fill: parent
        drag.target: parent

        onPressed: {
            order.beginDrag = Qt.point(order.x, order.y);
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
            console.log("Order tag: "+orderTag);
        }
        onReleased: {
            globalPosThis = waiterMain.mapFromItem(order, 0, 0)
            globalPosThis.x = globalPosThis.x + order.width * 0.95

            if (order.orderTag=="ToPay")
            {
                if (isInside(globalPosThis,globalPosNew,orderList.width,orderList.height))
                {
                    order.caught = true;
                    order.targetTag = "New"
                    console.log("Topay order dropped in new area")
                }
            }
            else if (order.orderTag=="New")
            {
                if (isInside(globalPosThis,globalPosToPay,outgoingList.width,outgoingList.height))
                {
                    order.caught = true;
                    order.targetTag = "ToPay"
                    console.log("New order dropped in topay area")
                }
            }

            if (isInside(globalPosThis,globalPosRemove,trashImage.width,trashImage.height) && !caught)
            {
                order.caught = true;
                order.targetTag = "Rejected"
                console.log(orderTag+" order dropped in rejected area")
            }
            else if (isInside(globalPosThis,globalPosPayed,moneyImage.width,moneyImage.height) && !caught)
            {
                order.caught = true;
                order.targetTag = "Payed"
                console.log(orderTag+" order dropped in payed area")
            }

            console.log("Global pos of object: "+globalPosThis)

            if(!order.caught) {
                console.log("Object was not caught in any proper area.")
                backAnimX.from = order.x
                backAnimX.to = beginDrag.x
                backAnimY.from = order.y
                backAnimY.to = beginDrag.y
                //if current object position != starting object pos => play animation and make object non iteractable
                if (order.x !== beginDrag.x && order.y !== beginDrag.y) {
                    order.enabled = false
                    seq.start()
                }
                //otherwise - reset parent list clipping and z positions
                else {
                    if (orderTag=="New") orderList.clip = true
                    else outgoingList.clip = true;
                    orderList.z = outgoingList.z = 0
                }
            }
            else {
                console.log("Order was caught and switched type.")
                if (orderTag=="New") orderList.clip = true
                else outgoingList.clip = true;
                orderList.z = outgoingList.z = 0

                readyOrder;
                switch (targetTag)
                {
                case "New":
                    orderboard.changeState(0)
                    break;
                case "Payed":
                    orderboard.changeState(1)
                    break;
                case "Rejected":
                    orderboard.changeState(2)
                    break;
                case "ToPay":
                    orderboard.changeState(3)
                    break;
                }
                order.Drag.active = false
            }
        }
    }

    SequentialAnimation {
        id:seq

        ParallelAnimation {
            id: backAnim
            PropertyAnimation { id: backAnimX; target: order; property: "x"; duration: 300; }
            PropertyAnimation { id: backAnimY; target: order; property: "y"; duration: 300; }
        }

        ScriptAction {
            script: {
                if ( orderTag == "New" ) orderList.clip = true
                else outgoingList.clip = true;
                orderList.z = outgoingList.z = 0
                order.enabled = true
                console.log("Sequential anim ended.")
            }
        }

    }

    Image {
        id: touchImage

        source: "qrc:/resources/images/fingerprint.png"
        fillMode: Image.PreserveAspectFit

        anchors.left: parent.left
        anchors.right: orderItemsView.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: Math.max(parent.width*0.02,10)
        anchors.rightMargin: Math.max(parent.width*0.01,10)
    }

    ListView {
        id: orderItemsView

        anchors.margins: borderWidth*1.5
        anchors.topMargin: borderWidth*3
        anchors.bottomMargin: borderWidth*3
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: parent.width * 0.8

        z: parent.z

        interactive: false

        spacing: itemSpacing

        model: orderItems
        delegate: OrderProductListElement { height: productHeight}
    }

    Rectangle {
        width: orderTime.font.pixelSize * 4
        height: borderWidth * 2.5
        anchors.top: parent.top
        anchors.topMargin: -3
        anchors.horizontalCenter: parent.horizontalCenter

        z: parent.z

        Text {
            id: orderTime
            text: model.timeSent
            color: borderColor
            font.pixelSize: borderWidth * 2.5
            font.bold: true
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
