import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {

    height: parent.height
    width: parent.width * 0.6
    anchors.centerIn: parent

    Text {
        id: timeDisplay
        text: Qt.formatTime(new Date(),"hh:mm")
        font.pixelSize: parent.height * 0.6
        anchors.centerIn: parent
    }

    Timer {
        id: timer
        interval: 1000
        repeat: true
        running: true

        onTriggered:
        {
            timeDisplay.text =  Qt.formatTime(new Date(),"hh:mm")
        }
    }
}
