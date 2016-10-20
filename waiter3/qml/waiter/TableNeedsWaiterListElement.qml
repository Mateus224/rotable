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

<<<<<<< HEAD
    Behavior on x { PropertyAnimation { duration: 500 } }

=======
>>>>>>> 2ba42cc0a24f99d9aa7fc960c051c99a0f0a6712
    Text {
        text: qsTr("Table ") + model.tableName
        font.pixelSize: parent.height * 0.35
        color: "#FFFFFF"
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 8
    }

<<<<<<< HEAD
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
=======
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
>>>>>>> 2ba42cc0a24f99d9aa7fc960c051c99a0f0a6712
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: {
            hideAnim.start()
<<<<<<< HEAD
//            needBoard.unneedTable(model.tableIdx)
=======
>>>>>>> 2ba42cc0a24f99d9aa7fc960c051c99a0f0a6712
        }
    }
}
