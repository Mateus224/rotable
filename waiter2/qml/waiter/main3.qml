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

        Layout.preferredWidth: 500
        Layout.preferredHeight: 50
    }

    Menu{
        id: menu

        Layout.preferredWidth: 150
        Layout.minimumWidth: 150
        //Layout.preferredHeight: 100

        Layout.columnSpan: 2
    }

    OrderList{
        id: orders
        Layout.columnSpan: 7

        height: parent.height - orderLabel.height
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

        Layout.row: 4
        Layout.column: 0

    }


}
