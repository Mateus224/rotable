import QtQuick 2.0
import "componentCreation.js" as CreateComponent

Rectangle {
    id: testButton
    x:800
    y:400
    width:100
    height:30
    color: "lightgray"

    MouseArea {

    id: mainWindow
    anchors.fill: parent

    onClicked: CreateComponent.createCategory(tableWindow,0);

    }

    Text{
        text: "create Table"
        font.pixelSize: 15
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}


