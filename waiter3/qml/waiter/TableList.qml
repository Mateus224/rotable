import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

ListView {
    id: tableList

    height: parent.height
    width: parent.width * 0.2
    spacing: 10

    ExclusiveGroup {
        id: tableExclusiveGroup
    }

    model: tables

    delegate: Button{
        id: tableListButton

        enabled: model.orderNumber == 0 ? false : true

        width:  parent.width
        checkable: true
        exclusiveGroup: tableExclusiveGroup
        property var connected: model.isConnected ? "Connected" : "Disconnected"
        text: "Table: " + model.name + ", " + model.id + "\nOrders: " + model.orderNumber + "\n" + connected
        anchors.horizontalCenter: parent.horizontalCenter

        onClicked: tables.sendToBoardOrder(model.id)
    }
}
