import QtQuick 2.5

ListView {

    id: orderList

    width: parent.width * 0.33

    spacing: Math.max(10,dataView.height*0.025)

    model: orderFilterNew

    snapMode: ListView.SnapToItem
    boundsBehavior: Flickable.StopAtBounds

    clip:true

    delegate: OrderListElement { orderTag: "New" }

    DropArea {
        id:incDrop
        anchors.fill: parent

        onEntered:
        {
            if (drag.source.orderTag == "ToPay")
            {
                console.log("drag entered new list!");
                drag.source.caught = true;
            }
            else console.log("wrong type drag entered new list!");
        }
        onExited:
        {
            if (drag.source.orderTag == "ToPay")
            {
                console.log("drag left new list!");
                drag.source.caught = false;
            }
            else console.log("wrong type drag left new list!");
        }
    }
}
