import QtQuick 2.5

import "TopBar/"
import "PullOutMenu/"

Rectangle {

    id: waiterMain

    property int leftMenuWidth: width * 0.2

    property color menuColor: "#0170bf"
    property color incomingColor: "#75d4f0"
    property color productBorderColor: "#bababa"

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
