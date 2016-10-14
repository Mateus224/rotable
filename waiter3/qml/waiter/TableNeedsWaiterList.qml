import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {

    id: needsWaiterBody

    anchors.fill: parent

    property int itemHeight: height * 1.1
    property int itemWidth: width * 0.2

    color: "#FFFF00"

    ListView {
        id: needsWaiterlist

        anchors.fill: parent
        anchors.leftMargin: needsWaiterBody.width * 0.05
        anchors.rightMargin: needsWaiterBody.width * 0.05
//        anchors.centerIn: parent
        orientation: ListView.Horizontal

        model: needBoard

        delegate: TableNeedsWaiterListElement {
            height: itemHeight
            width: itemWidth
        }

    }
}
