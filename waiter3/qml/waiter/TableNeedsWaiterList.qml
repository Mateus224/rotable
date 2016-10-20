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
<<<<<<< HEAD
=======
        anchors.leftMargin: needsWaiterBody.width * 0.05
        anchors.rightMargin: needsWaiterBody.width * 0.05
>>>>>>> 2ba42cc0a24f99d9aa7fc960c051c99a0f0a6712
//        anchors.centerIn: parent
        orientation: ListView.Horizontal

        model: needBoard

        delegate: TableNeedsWaiterListElement {
            height: itemHeight
            width: itemWidth
        }

    }
}
