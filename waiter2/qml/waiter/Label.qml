import QtQuick 2.3

Item {

    property alias text: labelText.text

    Text {
        id: labelText
        text: qsTr(parent.name)

        anchors.centerIn: parent
    }

    MouseArea {
        //ToDo:hide elements from menu
        anchors.fill: parent
        //onClicked: console.log("Button clicked!")
    }

    width: parent.width
    height: 50
}
