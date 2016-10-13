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

    SequentialAnimation {
        id: hideAnim
        NumberAnimation {
            target: needsWaiterBody
            property: "anchors.bottomMargin"
            duration: 300
            easing.type: Easing.InOutQuad
            to: -parent.height * 1.5
        }
        ScriptAction { script: needBoard.unneedTable(model.tableIdx); }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: {
            hideAnim.start()
//            needBoard.unneedTable(model.tableIdx)
        }
    }
}
