import QtQuick 2.5

ListView {

    id: outgoingList

    width: parent.width * 0.33

    spacing: Math.max(10,dataView.height*0.025)

    model: orderFilterToPay

    snapMode: ListView.SnapToItem
//    boundsBehavior: Flickable.StopAtBounds

    clip: true

    delegate: OrderListElement { orderTag: "ToPay"; targetTag: "None" }

    DropArea {
        id:outDrop
        anchors.fill: parent

        onEntered:
        {
            if (drag.source.orderTag == "New")
            {
                console.log("drag New entered ToPay list!");
                drag.source.caught = true;
                drag.source.targetTag = "ToPay"
            }
            else console.log("drag ToPay entered topay list!");
        }
        onExited:
        {
            if (drag.source.orderTag == "New")
            {
                console.log("drag New left ToPay list!");
                drag.source.caught = false;
                drag.source.targetTag = "None"
            }
            else console.log("drag ToPay left ToPay list!");
        }
    }
}
