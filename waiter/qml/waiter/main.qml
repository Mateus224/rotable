import QtQuick 2.0
import QtMultimedia 5.0
import "componentCreation.js" as CreateComponent

Rectangle {
    id: appWindow
    width: 900; height: 600
    MouseArea {
    //color:"#800000FF"
    id: bottleArea
    anchors.fill: parent
    //rotation: 4
    onPressed: CreateComponent.createSpriteObjects();
    }
    Image {
    id: dialer
    anchors.fill: parent
    //source: "pics/sky_vodka.png";
    }

    Component.onCompleted: CreateComponent.createSpriteObjects();


}

