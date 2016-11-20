import QtQuick 2.5

Rectangle {

    id: needsWaiterBody

    anchors.fill: parent

    property int itemHeight: height * 1.1
    property int itemWidth: width * 0.2

    color: "pink"

    ListView {
        id: needsWaiterlist

        anchors.fill: parent
        anchors.leftMargin: needsWaiterBody.width * 0.05
        anchors.rightMargin: needsWaiterBody.width * 0.05
        orientation: ListView.Horizontal

        model: needBoard

        delegate: TableNeedsWaiterListElement {
            height: itemHeight
            width: itemWidth
        }

    }
}
