import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

ListView {
    id: tableList

    property int tableElementHeight: Math.max(30,dataView.height * 0.1)

    width: parent.width * 0.3
    height: tables.count * tableElementHeight

    interactive: false

    model: tables

    delegate: TableListElement { height: tableElementHeight}

}
