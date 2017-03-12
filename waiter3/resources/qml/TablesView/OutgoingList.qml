import QtQuick 2.5

ListView {

    id: outgoingList

    width: parent.width * 0.33

    spacing: Math.max(12,dataView.height*0.02)

    model: orderFilterToPay

    snapMode: ListView.SnapToItem
//    boundsBehavior: Flickable.StopAtBounds

    clip: true

    delegate: OrderListElement { orderTag: "ToPay"; targetTag: "None"; borderColor: waiterMain.menuColor }
}
