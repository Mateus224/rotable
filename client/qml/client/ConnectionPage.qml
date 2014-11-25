import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    color: "#00000000" // max alpha!

    Rectangle {
        id: rectOnConnecting
        anchors.centerIn: parent
        color: "#8f214d"
        width: textOnConnecting.width * 1.2
        height: textOnConnecting.height * 1.2
        radius: 10

        Text {
            id: textOnConnecting
            text: "CONNECTING   "
            font.family: "FreeSans"
            color: "#FFFFFF"
            font.pointSize: 22
            anchors.centerIn: parent
            font.bold: true
        }

        Timer {
            property var dots: 0

            interval: 500;
            running: true;
            repeat: true

            onTriggered: {
                dots = ++dots % 4

                var text = "CONNECTING";
                for (var i = 0; i < 3; ++i) {
                    if (i < dots) {
                        text += "."
                    } else {
                        text += " "
                    }
                }

                var size = textOnConnecting.width

                textOnConnecting.text = text
                textOnConnecting.width = size
            }
        }
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
