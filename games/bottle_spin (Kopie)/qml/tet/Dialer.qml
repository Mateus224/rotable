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
    color: "transparent" //"#800000FF"//



    RotationAnimation {
	id: rotaryReleaseAnimation
    duration : 2000
	target: dialer
	property: "rotation"
    easing.type: Easing.OutQuad
    //direction: RotationAnimation.Counterclockwise
    }

    // the numbers layer
/*
    Rectangle {
	id: numbers
	anchors.fill: parent
    color: "transparent"

	Repeater {
        model: 12
	    delegate: Rectangle {
        width: 30
        height: 30
		color: "transparent"
        x: dialerView.width / 2 + 300 * Math.cos(index * Dialer.digitAngle) - 15
        y: dialerView.height / 2 - 300 * Math.sin(index * Dialer.digitAngle) - 15

		Text {
		    color: "black"
            font.pointSize: 15
		    anchors.centerIn: parent
            text: (index + 1) % 13
		}
	    }
    }

	anchors.centerIn: parent
    }*/

    // the rotating dialer layer

    Image {
	id: dialer
	anchors.fill: parent
    source: "pics/sky_vodka.png";
    }






    MouseArea {
    //color:"#800000FF"
    id: bottleArea
	anchors.fill: parent
    //rotation: 45
	onPositionChanged: Dialer.dialerMoved(mouse)
	onReleased: Dialer.dialerReleased(mouse)
	onPressed: Dialer.dialerPressed(mouse)
    }

    Component.onCompleted: Dialer.initialize()
}
