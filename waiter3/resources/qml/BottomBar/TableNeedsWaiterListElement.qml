import QtQuick 2.5

Rectangle {

    id: needsWaiterBody

    color: "#FF0000"

    radius: width / 15

    anchors.bottom: parent.bottom
    anchors.bottomMargin: -parent.height*0.2

    Text {
        text: qsTr("Table ") + model.tableName
        font.pixelSize: parent.height * 0.38
        color: "#FFFFFF"
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 8
    }

    NumberAnimation {
        id: hideAnim

        target: needsWaiterBody
        property: "anchors.bottomMargin"
        duration: 300
        easing.type: Easing.InOutQuad
        to: -parent.height * 1.5

        onRunningChanged: {
            if (!hideAnim.running) needBoard.unneedTable(model.tableIdx)
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: {
            hideAnim.start()
        }
    }
}
