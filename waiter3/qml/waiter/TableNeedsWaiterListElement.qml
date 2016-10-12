import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {

    id: needsWaiterBody

    color: "#FF0000"

    radius: width / 15

    anchors.bottom: parent.bottom
    anchors.bottomMargin: -parent.height*0.2

    Behavior on x { PropertyAnimation { duration: 500 } }

    Text {
        text: qsTr("Table ") + model.tableName
        font.pixelSize: parent.height * 0.35
        color: "#FFFFFF"
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 8
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: needBoard.unneedTable(model.tableIdx)
    }
}
