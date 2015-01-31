import QtQuick 2.0
import "componentCreation.js" as CreateComponent

Rectangle {
    id: a
    width: 100
    height: 62
    color:"#800000FF"

    Text {
        id: name0
        text: qsTr("table:")

    font.pointSize: 10
    anchors.centerIn: parent
    }

}
