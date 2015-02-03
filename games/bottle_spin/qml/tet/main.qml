import QtQuick 2.0

import "RotaryDialer.js" as Dialer



Rectangle {
    width: 640
    height: 640

    Image {
	anchors.fill: parent
    source:  "pics/background.png"
	fillMode: "Tile"
    }



    Dialer {
    //onNumberEntered: dialerOutput.text += number
    }

}
