import QtQuick 2.5
import QtGraphicalEffects 1.0

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

    BottomBar {
        id: bottomBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    Rectangle {
        id: rightPanel
        anchors.left: outgoingList.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: bottomBar.top

        DropShadow {
            anchors.fill: moneyImage
            radius: 25
            samples: 51
            spread: 0.5
            color: "#ff00FF00"
            source: moneyImage
        }

        DropShadow {
            anchors.fill: trashImage
            radius: 25
            samples: 51
            spread: 0.4
            color: "#ffFF0000"
            source: trashImage
        }

        Image {
            id: moneyImage
            source: "qrc:/resources/images/money.svg"
            fillMode: Image.PreserveAspectFit
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.verticalCenter
        }

        Image {
            id: trashImage
            source: "qrc:/resources/images/trash.svg"
            fillMode: Image.PreserveAspectFit
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.top: parent.verticalCenter
        }
    }
}
