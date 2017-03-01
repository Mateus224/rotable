import QtQuick 2.5

ListView {

    id: outgoingList

    width: parent.width * 0.33

    spacing: Math.max(10,dataView.height*0.02)

    model: orderFilterToPay

    snapMode: ListView.SnapToItem
//    boundsBehavior: Flickable.StopAtBounds

    clip: true

    delegate: OrderListElement { orderTag: "ToPay"; targetTag: "None"; borderColor: waiterMain.menuColor }

    DropArea {
        id:outDrop
        anchors.fill: parent

        onEntered:
        {
            if (drag.source.orderTag === "New")
            {
//                console.log("drag New entered ToPay list!");
//                drag.source.caught = true;
//                drag.source.targetTag = "ToPay"
//                drag.source.border.color = waiterMain.menuColor
            }
        }
        onExited:
        {
            if (drag.source.orderTag === "New")
            {
//                console.log("drag New left ToPay list!");
//                drag.source.caught = false;
//                drag.source.targetTag = "None"
//                drag.source.border.color = waiterMain.incomingColor
            }
        }
    }
}
