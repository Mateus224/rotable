import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    color: "#00000000" // max alpha!

    Rectangle {
        id: rectTouchToStart
        anchors.centerIn: parent
        color: "#FFFFFF"
        width: textOTouchToStart.width * 1.2
        height: textOTouchToStart.height * 1.2
        //radius: 10

        Text {
            id: textOTouchToStart
            text: "TOUCH DISPLAY TO START"
            font.family: "FreeSans"
            color: "#000000"
            font.pointSize: 20
            anchors.centerIn: parent
            //font.bold: true
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: client.state = "STARTSCREEN"
    }

    Image {
        id: logo
        source: "qrc:/client/resources/rotable_logo.png"

        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 10

        width: 250
        fillMode: Image.PreserveAspectFit
        antialiasing: true
    }
}
