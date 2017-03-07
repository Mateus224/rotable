import QtQuick 2.5

Rectangle {
    id: container

    height: order.height + emptySpace.height
    width: listWidth

    color: "transparent"

    Drag.active: dragArea.drag.active

    z: (dragArea.pressed || dragArea.drag.active || seq.running) ? 1 : 0

    Rectangle {
        id: emptySpace
        height: waiterMain.height * 0.01
        color: "transparent"

        anchors.top: parent.top
        width: listWidth
    }

    property string borderColor
    property string orderTag
    property string targetTag

    property var globalPosThis
    property var globalPosNew : waiterMain.mapFromItem(orderList, 0, 0)
    property var globalPosToPay : waiterMain.mapFromItem(outgoingList, 0, 0)
    property var globalPosRemove : waiterMain.mapFromItem(trashImage, 0, 0)
    property var globalPosPayed : waiterMain.mapFromItem(moneyImage, 0, 0)

    property point beginDrag: Qt.point(x,y)

    property int listWidth: Math.max(100,orderList.width)

    function isInside(objectPos,targetPos,targetWidth,targetHeight)
    {
        return ( objectPos.x >= targetPos.x && objectPos.x <= targetPos.x+targetWidth
                && objectPos.y >= targetPos.y && objectPos.y <= targetPos.y+targetHeight )
    }

    function handleDragging()
    {
        globalPosThis = waiterMain.mapFromItem(container, 0, 0)
        globalPosThis.x = globalPosThis.x + container.width * 0.95
        if (isInside(globalPosThis,globalPosNew,orderList.width,orderList.height))
            container.borderColor = waiterMain.incomingColor
        else if (isInside(globalPosThis,globalPosToPay,outgoingList.width,outgoingList.height))
            container.borderColor = waiterMain.menuColor
        else if (isInside(globalPosThis,globalPosRemove,trashImage.width,trashImage.height))
            container.borderColor = waiterMain.removeColor
        else if (isInside(globalPosThis,globalPosPayed,moneyImage.width,moneyImage.height))
            container.borderColor = waiterMain.payedColor
        else container.borderColor = orderTag=="New" ? waiterMain.incomingColor : waiterMain.menuColor
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

Rectangle{
    id: order
    anchors.top: emptySpace.bottom

    property int productHeight: Math.max(40,dataView.height * 0.08)
    property int borderWidth: Math.max(4,orderList.width * 0.013)
    property int itemSpacing: Math.max(10,dataView.height*0.02)
    property int listHeight: orderItemsView.count * productHeight + 6 * borderWidth + (orderItemsView.count-1) * itemSpacing

    property bool caught: false

    width: listWidth
    height: model.itemCount > 0 ? listHeight : 0

    border.width: borderWidth
    border.color: borderColor
    radius: width / 15

    MouseArea{
        id:dragArea

        anchors.fill: parent
        drag.target: container

        onPressed: {
            beginDrag = Qt.point(container.x, container.y);
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
            globalPosThis = waiterMain.mapFromItem(container, 0, 0)
            globalPosThis.x = globalPosThis.x + container.width * 0.95

            if (container.orderTag=="ToPay")
            {
                if (isInside(globalPosThis,globalPosNew,orderList.width,orderList.height))
                {
                    order.caught = true;
                    targetTag = "New"
                    console.log("Topay order dropped in new area")
                }
            }
            else if (container.orderTag=="New")
            {
                if (isInside(globalPosThis,globalPosToPay,outgoingList.width,outgoingList.height))
                {
                    order.caught = true;
                    targetTag = "ToPay"
                    console.log("New order dropped in topay area")
                }
            }

            if (isInside(globalPosThis,globalPosRemove,trashImage.width,trashImage.height) && !order.caught)
            {
                order.caught = true;
                targetTag = "Rejected"
                console.log(orderTag+" order dropped in rejected area")
            }
            else if (isInside(globalPosThis,globalPosPayed,moneyImage.width,moneyImage.height) && !order.caught)
            {
                order.caught = true;
                targetTag = "Payed"
                console.log(orderTag+" order dropped in payed area")
            }

            console.log("Global pos of object: "+globalPosThis)

            if(!order.caught) {
                console.log("Object was not caught in any proper area, returning to intial position.")
                backAnimX.from = container.x
                backAnimX.to = beginDrag.x
                backAnimY.from = container.y
                backAnimY.to = beginDrag.y
                //if current object position != starting object pos => play animation and make object non iteractable
                if (container.x !== beginDrag.x && container.y !== beginDrag.y) {
                    container.enabled = false
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
            PropertyAnimation { id: backAnimX; target: container; property: "x"; duration: 300; }
            PropertyAnimation { id: backAnimY; target: container; property: "y"; duration: 300; }
        }

        ScriptAction {
            script: {
                if ( orderTag == "New" ) orderList.clip = true
                else outgoingList.clip = true;
                orderList.z = outgoingList.z = 0
                container.enabled = true
                console.log("Sequential anim ended.")
            }
        }

    }

    Image {
        id: touchImage

        source: "qrc:/resources/images/fingerprint.png"
        fillMode: Image.PreserveAspectFit

        anchors.left: orderItemsView.right
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: Math.max(parent.width*0.02,10)
        anchors.rightMargin: Math.max(parent.width*0.01,10)
    }

    ListView {
        id: orderItemsView

        anchors.margins: order.borderWidth*1.5
        anchors.topMargin: order.borderWidth*3
        anchors.bottomMargin: order.borderWidth*3
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width * 0.8

        z: parent.z

        interactive: false

        spacing: order.itemSpacing

        model: orderItems
        delegate: OrderProductListElement { height: order.productHeight}
    }

    Rectangle {
        width: orderTime.font.pixelSize * 4
        height: order.borderWidth * 3
        anchors.top: parent.top
        anchors.topMargin: -3
        anchors.horizontalCenter: parent.horizontalCenter

        z: parent.z

        Text {
            id: orderTime
            text: model.timeSent
            color: borderColor
            font.pixelSize: order.borderWidth * 3.6
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -order.borderWidth * 0.6
        }
    }
}

}
