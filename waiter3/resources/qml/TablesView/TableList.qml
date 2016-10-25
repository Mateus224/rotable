import QtQuick 2.5

ListView {
    id: tableList

    property int tableElementHeight: Math.max(30,dataView.height * 0.1)

    width: waiterMain.leftMenuWidth
    height: tables.count * tableElementHeight

    interactive: false

    clip: true

    model: tables

    delegate: TableListElement { height: tableElementHeight}

}
