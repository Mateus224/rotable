import QtQuick 2.0

import "RotaryDialer.js" as Dialer

Rectangle {
    id: dialerView

    signal numberEntered(int number)

    width: 340
    height: 340
    anchors.centerIn: parent
    color: "transparent"

    RotationAnimation {
	id: rotaryReleaseAnimation
	duration : 1000
	target: dialer
	property: "rotation"
	easing.type: Easing.OutBounce
	direction: RotationAnimation.Counterclockwise
    }

    // the numbers layer

    Rectangle {
	id: numbers
	anchors.fill: parent
	color: "transparent"

	Repeater {
	    model: 10
	    delegate: Rectangle {
		width: 30
		height: 30
		color: "transparent"
		x: dialerView.width / 2 + 130 * Math.cos(index * Dialer.digitAngle) - 15
		y: dialerView.height / 2 - 130 * Math.sin(index * Dialer.digitAngle) - 15

		Text {
		    color: "black"
            font.pointSize: 15
		    anchors.centerIn: parent
		    text: (index + 1) % 10
		}
	    }
	}

	anchors.centerIn: parent
    }

    // the rotating dialer layer

    Image {
	id: dialer
	anchors.fill: parent
    source: "qrc:///pics/sky_vodka.png";
    }

    // the dialer stop layer

    Image {
	id: dialerStop
	anchors.bottom: parent.bottom
	anchors.right: parent.right
    source: "qrc://pics/rotary_stop.png"
    }

    MouseArea {
	anchors.fill: parent
	onPositionChanged: Dialer.dialerMoved(mouse)
	onReleased: Dialer.dialerReleased(mouse)
	onPressed: Dialer.dialerPressed(mouse)
    }

    Component.onCompleted: Dialer.initialize()
}
