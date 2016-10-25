import QtQuick 2.5

Rectangle {

    id: buttonBody

    property string nameText
    property bool selected: false

    width: parent.width

    anchors.left: parent.left
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.margins: parent.borderThickness

    color: selected ? "#000FDF" : "#FFFFFF"

    Text {
        id: optionName
        anchors.centerIn: parent
        text: nameText + langObject.emptyString
        font.pixelSize: parent.height * 0.3
        color: selected ? "#FFFFFF" : "#000000"
    }

    Text {
        id: selectedArrow

        visible: selected

        anchors.right: parent.right
        anchors.rightMargin: parent.width * 0.02
        anchors.verticalCenter: parent.verticalCenter

        text: ">"
        font.bold: true
        font.pixelSize: parent.height * 0.4
        color: "#FFFFFF"
    }
}
