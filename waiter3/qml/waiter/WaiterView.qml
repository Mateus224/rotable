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
        anchors.bottom: parent.bottom
        anchors.left: parent.left
    }

    Rectangle {
        id: wtf
        anchors.left: tableList.right
        anchors.right: parent.right
        anchors.top: timeBar.bottom
        anchors.bottom: parent.bottom
        color: "#FEDCBA"
    }
}
