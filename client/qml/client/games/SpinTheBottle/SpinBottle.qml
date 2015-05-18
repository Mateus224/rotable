import QtQuick 2.0
import "SpinBottle.js" as SpinBottle

Rectangle{
    anchors.fill: parent


    Image {
        //anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
        width: parent.width
        source:  "qrc:/client/games/SpinTheBottle/qml/client/games/SpinTheBottle/pics/background.png"
        //fillMode: "Tile"
    }
    Image {
        x:parent.width-45
        y:10
        //anchors.right: 20
        id: close
        source: "qrc:/client/games/SpinTheBottle/qml/client/games/SpinTheBottle/pics/close.png"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                client.state = "STARTSCREEN";
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        id: spinBottle
        rotation: 0
        width: 125
        height: 480
        anchors.centerIn: parent
        color:  "transparent"//"#800000FF"//


        RotationAnimation {
        id: rotaryReleaseAnimation
        target: dialer
        property: "rotation"
        easing.type: Easing.OutQuad
        }

        Image {
        id: dialer
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
        width: parent.width/3.75
        source: "qrc:/client/games/SpinTheBottle/qml/client/games/SpinTheBottle/pics/sky_vodka.png";
        }

        MouseArea {
        //color:"#800000FF"
        id: bottleArea
        anchors.fill: parent
        onPositionChanged: SpinBottle.dialerMoved(mouse)
        onReleased: SpinBottle.dialerReleased(mouse)
        onPressed: SpinBottle.dialerPressed(mouse)
        }

        Component.onCompleted: SpinBottle.initialize()
    }
}
