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

            DropArea {
                id: payedArea
                anchors.fill: parent

                onEntered:
                {
                    if (drag.source.orderTag==="New" || drag.source.orderTag=="ToPay")
                    {
    //                    console.log("drag "+drag.source.orderTag+" entered Money Button!");
    //                    drag.source.caught = true;
    //                    drag.source.targetTag = "Payed"
    //                    drag.source.border.color = "#00FF00"
                    }
                }
                onExited:
                {
                    if (drag.source.orderTag==="New" || drag.source.orderTag=="ToPay")
                    {
    //                    console.log("drag "+drag.source.orderTag+" exited Trash Button!");
    //                    drag.source.caught = false;
    //                    drag.source.targetTag = "None"
    //                    if (drag.source.orderTag=="New") drag.source.border.color = waiterMain.incomingColor
    //                    else drag.source.border.color = waiterMain.menuColor
                    }
                }
            }
        }

        Image {
            id: trashImage
            source: "qrc:/resources/images/trash.svg"
            fillMode: Image.PreserveAspectFit
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.top: parent.verticalCenter

            DropArea {
                id: removeArea
                anchors.fill: parent

                onEntered:
                {
    //                if (drag.source.orderTag=="New" || drag.source.orderTag=="ToPay")
    //                {
    //                    console.log("drag "+drag.source.orderTag+" entered Trash Button!");
    //                    drag.source.caught = true;
    //                    drag.source.targetTag = "Rejected"
    //                    drag.source.border.color = "#FF0000"
    //                }
                }
                onExited:
                {
    //                if (drag.source.orderTag=="New" || drag.source.orderTag=="ToPay")
    //                {
    //                    console.log("drag "+drag.source.orderTag+" exited Trash Button!");
    //                    drag.source.caught = false;
    //                    drag.source.targetTag = "None"
    //                    if (drag.source.orderTag=="New") drag.source.border.color = waiterMain.incomingColor
    //                    else drag.source.border.color = waiterMain.menuColor
    //                }
                }
            }
        }
    }
}
