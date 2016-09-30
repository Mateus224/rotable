import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {

    width: parent.width
    height: parent.height * 0.1
    anchors.top: parent.top
    color: "#40E0D0"

    SimpleClock {
        id: clock
        anchors.centerIn: parent
        height: parent.height
    }
}
