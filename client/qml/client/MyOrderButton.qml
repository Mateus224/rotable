import QtQuick 2.0

Rectangle {
    color: "#FFFFFF"
    width: buttonLabel.width * 1.2
    height: buttonLabel.height * 1.2

    Text {
        id: buttonLabel
        text: "MY ORDER"
        font.family: "FreeSans"
        color: "#000000"
        font.pointSize: 20
        anchors.centerIn: parent
    }
}
