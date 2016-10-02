import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {

    id: waiterMain

    TimeBar {
        id: timeBar
    }

    TableList {
        id: tableList
        anchors.top: timeBar.bottom
        anchors.left: parent.left
    }
}
