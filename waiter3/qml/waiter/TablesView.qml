import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {

    id: tablesMain

    property int orderListMargin: Math.max(10,width*0.35*0.04)

    TableList {
        id: tableList
        height: parent.height
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
        anchors.bottom: parent.bottom
    }
}
