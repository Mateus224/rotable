import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    anchors.topMargin: parent.height * 0.2
    anchors.leftMargin: parent.width * (1.0 - 0.805) / 2.0
    anchors.rightMargin: parent.width * (1.0 - 0.805) / 2.0
    anchors.bottomMargin: parent.height * (0.09125 + 0.10 + 0.125)
    color: "#3f494a"
    Rectangle {
        anchors.fill: parent
        anchors.margins: parent.height * 0.02

        color: "#000000"

        Text {
            id: tempText
            text: "Sending..."
            font.family: "FreeSans"
            color: "#AAAAAA"
            font.bold: true
            font.pixelSize: parent.height * 0.1
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.capitalization: Font.AllUppercase
        }
    }


}

