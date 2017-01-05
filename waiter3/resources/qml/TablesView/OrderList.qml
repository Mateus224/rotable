import QtQuick 2.5

ListView {

    id: orderList

    width: parent.width * 0.33

    spacing: Math.max(10,dataView.height*0.02)

    model: orderFilterNew

    snapMode: ListView.SnapToItem
//    boundsBehavior: Flickable.StopAtBounds

    clip:true

    delegate: OrderListElement { orderTag: "New"; targetTag: "None"; borderColor: waiterMain.incomingColor }

    DropArea {
        id:incDrop
        anchors.fill: parent

        onEntered:
        {
            if (drag.source.orderTag === "ToPay")
            {
                console.log("drag ToPay entered New list!");
                drag.source.caught = true;
                drag.source.targetTag = "New"
                drag.source.border.color = waiterMain.incomingColor
            }
        }
        onExited:
        {
            if (drag.source.orderTag === "ToPay")
            {
                console.log("drag ToPay left new list!");
                drag.source.caught = false;
                drag.source.targetTag = "None"
                drag.source.border.color = waiterMain.menuColor
            }
        }
    }
}
