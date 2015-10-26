import QtQuick 2.0

Rectangle {
    id:screensaverPage
    anchors.fill: parent
    color: "#00000000" // max alpha!

    Rectangle {

        id: rectTouchToStart
        anchors.centerIn: parent
        width: parent.width
        height: parent.height * 0.1

        Image {
            id: backgroundImage
            anchors.fill: parent
            source: "qrc:/client/resources/bg_categories.png"
        }

        Text {
            id: textOnTouchToStart
            text: "TOUCH DISPLAY TO START"
            font.family: "FreeSans"
            color: "#FFFFFF"
            anchors.centerIn: parent
            font.pixelSize: parent.height * 0.70
        }
    }
    property string startscreen: "STARTSCREEN"
    MouseArea {
        id:te
        anchors.fill: parent
        onClicked: client.state = startscreen
    }

    /*Image {
        id: logo
        source: "qrc:/client/resources/rotable_logo.png"

        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 10

        width: 250
        fillMode: Image.PreserveAspectFit
        antialiasing: true
    }*/
}
