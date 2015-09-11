import QtQuick 2.3
import QtQuick.Layouts 1.1

GridLayout{
    id: mainGrid
    columns: 2
    anchors.fill: parent

    columnSpacing: 10

    Layout.preferredWidth: 150

    Label{
        id: menuLabel

        text: qsTr("Menu")

        Layout.preferredWidth: 150
        Layout.preferredHeight: 50
        Layout.maximumHeight: 50

    }

    Label{
        id: orderLabel

        text: qsTr("Orders")

        height: 50

        width: parent.width - menu.width
    }

    Menu{
        id: menu

        Layout.preferredWidth: 150
        Layout.minimumWidth: 150
        //Layout.preferredHeight: 100

        Layout.rowSpan: 2
    }

    OrderList{
        id: orders
        Layout.rowSpan: 7

        height: parent.height - orderLabel.height
        width: parent.width - menu.width
    }

    Label{
        id: tableLabel

        text: qsTr("Tables")

        Layout.preferredWidth: 150
        Layout.minimumWidth: 150

    }

    TableList{
        Layout.preferredWidth: 150
        Layout.minimumWidth: 150

        Layout.preferredHeight: 200

        Layout.column: 0
        Layout.row: 4


    }


}
