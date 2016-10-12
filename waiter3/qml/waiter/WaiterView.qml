import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {

    id: waiterMain

    property int leftMenuWidth: width * 0.2

    TimeBar {
        id: timeBar
    }

    DataView {
        id: dataView

        anchors.top: timeBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }

    PullOutMenu {
        id: pulloutMenu
        anchors.top: timeBar.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        menuWidth: leftMenuWidth
    }
}
