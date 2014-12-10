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

    Rectangle {/*
	border.width: 1
	border.color: "black"
	anchors.top: parent.top
	anchors.left: parent.left
	anchors.right: parent.right
	anchors.topMargin: 60
	anchors.margins: 10
	height: dialerOutput.height

	Text {
	    id: dialerOutput
	    text: ""
	    font.pointSize: 15
	    elide: Text.ElideLeft
	}
    */
    }

    Dialer {
    //onNumberEntered: dialerOutput.text += number
    }
    /*
    Rectangle {
            id : theTimer
            x : 20; y: 20
            width : 30 ; height: 50
            color: "#707070"

            Text {

                    //text: seconds
                    font.pointSize: 12; font.bold: true
                    font.family: "Courier"
                    anchors.centerIn: parent
                }
    }



    Timer{
        id:timer01
        interval: 100
        repeat: true
        running: true
        //onTriggered:{if(enabled) seconds++;}
    }
*/
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


        Timer  {
            id: elapsedTimer
            interval: 100;
            running: true;
            repeat: true;
            onTriggered: Dialer.timeChanged()
        }

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
