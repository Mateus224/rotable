import QtQuick 2.5

Rectangle {

    id: bototmBarLayout

    width: parent.width
    height: Math.max(50,parent.height * 0.14)

    Rectangle {
        id: empty
        width: waiterMain.leftMenuWidth
        height: parent.height
        anchors.left: parent.left
        anchors.top: parent.top
    }

    Rectangle {
        id: incText

        height: parent.height * 0.4
        width: waiterMain.width * 0.33
        anchors.left: empty.right
        anchors.top: parent.top

        Text {
            text: qsTr("Incoming") + langObject.emptyString
            font.pixelSize: parent.height * 0.8
            anchors.centerIn: parent
        }
    }

    Rectangle {

        height: parent.height * 0.4
        width: waiterMain.width * 0.33
        anchors.left: incText.right
        anchors.top: parent.top

        Text {
            text: qsTr("Outgoing") + langObject.emptyString
            font.pixelSize: parent.height * 0.8
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: needsWaiterRect
        height: parent.height * 0.6
        anchors.right: toPaySum.left
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        TableNeedsWaiterList { id: needsWaiterList}
    }

    Rectangle {
        id: toPaySum
        height: parent.height * 0.6
        width: parent.width * 0.2
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Text {
            text: qsTr("To Pay: ") + orderboard.ordersPrice.toFixed(2) +" €" + langObject.emptyString
            anchors.centerIn: parent
            font.pixelSize: Math.min(parent.height * 0.5, parent.width * 0.1)
        }
    }
}
