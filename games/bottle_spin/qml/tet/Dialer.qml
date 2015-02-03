import QtQuick 2.0

import "RotaryDialer.js" as Dialer
//import "timer.js" as timer

Rectangle {
    id: dialerView

    //signal numberEntered(int number)
    rotation: 0
    width: 125
    height: 480
    anchors.centerIn: parent
    color:  "transparent"//"#800000FF"//



    RotationAnimation {
	id: rotaryReleaseAnimation
    //duration : 2000
	target: dialer
    property: "rotation"
    easing.type: Easing.OutQuad
    //running: true
    }

    Image {
	id: dialer
	anchors.fill: parent
    source: "pics/sky_vodka.png";
    }






    MouseArea {
    //color:"#800000FF"
    id: bottleArea
	anchors.fill: parent
	onPositionChanged: Dialer.dialerMoved(mouse)
	onReleased: Dialer.dialerReleased(mouse)
	onPressed: Dialer.dialerPressed(mouse)
    }

    Component.onCompleted: Dialer.initialize()
}
