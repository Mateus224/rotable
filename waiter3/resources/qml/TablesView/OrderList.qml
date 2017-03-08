import QtQuick 2.5

ListView {

    id: orderList

    width: parent.width * 0.33

    spacing: Math.max(5,dataView.height*0.01)

    model: orderFilterNew

    snapMode: ListView.SnapToItem
//    boundsBehavior: Flickable.StopAtBounds

    clip:true

    delegate: OrderListElement { orderTag: "New"; targetTag: "None"; borderColor: waiterMain.incomingColor }
}
