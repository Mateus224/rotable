import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

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
