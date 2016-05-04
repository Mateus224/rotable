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

    }

    Rectangle {
        id: spinBottle
        rotation: 0
        width: 125
        height: 480
        //height: parent.height
        //width: parent.width/3.75
        anchors.centerIn: parent
        color:  "transparent"

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

    CloseButton{
        x:parent.width-50
        y:25
    }
    CloseButton{
        x:25
        y:25
    }
    CloseButton{
        x: 25
        y:parent.height-50
    }
    CloseButton{
        x:parent.width-50
        y:parent.height-50
    }

    Rectangle
    {
        rotation: 0
        width: parent.height/3
        height: parent.width/5
        x:parent.width /3
        y:(parent.height*4) /5
        color: "transparent"
        Image {
            width: parent.width
            height: parent.height
            source: "qrc:/client/games/SpinTheBottle/qml/client/games/SpinTheBottle/pics/spin-the-bottle-ny2.png";
            }
    }
    Rectangle
    {
        rotation: 90
        width: parent.width/3
        height: parent.height/5
        x:-(parent.width/15)
        y:parent.height/2-(parent.height/10)//-50
        color: "transparent"
        Image {
            width: parent.width
            height: parent.height
            source: "qrc:/client/games/SpinTheBottle/qml/client/games/SpinTheBottle/pics/spin-the-bottle-ny2.png";
            }
    }
    Rectangle
    {
        rotation: 180
        width: parent.height/3
        height: parent.width/5
        x:parent.width /3
        y:0
        color: "transparent"
        Image {
            width: parent.width
            height: parent.height
            source: "qrc:/client/games/SpinTheBottle/qml/client/games/SpinTheBottle/pics/spin-the-bottle-ny2.png";
            }
    }
    Rectangle
    {
        rotation: 270
        width: parent.width/3
        height: parent.height/5
        x:(parent.width*4)/5- (parent.width/15)
        y:parent.height/2-(parent.height/10)
        color: "transparent"
        Image {
            width: parent.width
            height: parent.height
            source: "qrc:/client/games/SpinTheBottle/qml/client/games/SpinTheBottle/pics/spin-the-bottle-ny2.png";
            }
    }

}
