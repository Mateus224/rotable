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

    Rectangle {
        //anchors.fill: parent
        id: spinBottle
        rotation: 0
        width: 125
        height: 480
        //height: parent.height
        //width: parent.width/3.75
        anchors.centerIn: parent
        color:  "transparent"//"#800000FF"//

        RotationAnimation {
            id: rotaryReleaseAnimation
            target: dialer
            property: "rotation"
            easing.type: Easing.OutQuad
            }

        Image {
            anchors.fill: parent
            //height: parent.height
            //width: parent.width
            id: dialer
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

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
    Rectangle{
        color: "transparent"
        width: 30
        height: 30
        x:parent.width-45
        y:20
        MouseArea{
            anchors.fill: parent
            onClicked: {
                client.state = "STARTSCREEN";
            }
        }

        Image {
            anchors.fill: parent
            //anchors.right: 20
            id: close
            width: 20
            height: 20
            source: "qrc:/client/games/SpinTheBottle/qml/client/games/SpinTheBottle/pics/close.png"
        }
    }

}
