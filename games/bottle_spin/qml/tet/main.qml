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

    Item  {
        id: root
        width: 200; height: 230

        property double startTime: 0
        property int secondsElapsed: 0

        function restartCounter()  {

                root.startTime = 0;

            }

/*
        function timeChanged()  {
            if(root.startTime==0)
            {
                root.startTime = new Date().getTime(); //returns the number of milliseconds since the epoch (1970-01-01T00:00:00Z);
            }
            var currentTime = new Date().getTime();
            var timeDiff=(currentTime-startTime)/50;
            root.secondsElapsed = timeDiff;
            if (timeDiff==200)
            {
                return 1
            }

        }
*/

/*
        Timer  {
            id: elapsedTimer
            interval: 100;
            running: true;
            repeat: true;
            //onTriggered: Dialer.timeChanged()
        }
 */
        Text {
            id: counterText
            text: root.secondsElapsed

        }
    }


    Image {
    source: "pics/close.png"
	anchors.right: parent.right
	anchors.top: parent.top
	anchors.margins: 5

	MouseArea {
	    anchors.fill: parent
	    onClicked: Qt.quit()
	}
    }
}
