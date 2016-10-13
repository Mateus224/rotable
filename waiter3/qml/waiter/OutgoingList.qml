import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

ListView {

    id: outgoingList

    width: parent.width * 0.33

    clip:true

    Rectangle {
        id: test
        color: "#00FFFF"
        anchors.fill: parent
    }
}
