import QtQuick 2.5

import "../BottomBar/"

Rectangle {

    id: tablesMain

    property int orderListMargin: Math.max(10,width*0.35*0.04)

    TableList {
        id: tableList
        anchors.top: parent.top
        anchors.bottom: bottomBar.top
        anchors.left: parent.left
    }

    OrderList {
        id: orderList
        anchors.left: tableList.right
        anchors.top: parent.top
        anchors.bottom: bottomBar.top
        anchors.margins: orderListMargin
    }

    OutgoingList {
        id: outgoingList
        anchors.left: orderList.right
        anchors.top: parent.top
        anchors.bottom: bottomBar.top
        anchors.margins: orderListMargin
    }

    RightPanel {
        id: rightPanel
        anchors.left: outgoingList.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: bottomBar.top
    }

    BottomBar {
        id: bottomBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
