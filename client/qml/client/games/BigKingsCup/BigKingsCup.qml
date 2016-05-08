import QtQuick 2.5
import QtQuick.Particles 2.0
import "KingsCupFunktions.js" as KingsCupFunktions
import "../ReadInformationFile.js" as ReadInformationFile
import "../SpinTheBottle/"
import"../"

Item {
    id: window
    width: parent.width
    height: parent.height
    anchors.centerIn: parent.Center

    // Let's draw the sky...
    Rectangle {
        anchors { left: parent.left; top: parent.top; right: parent.right; bottom: parent.verticalCenter }
        gradient: Gradient {
            GradientStop {
                position: 0.0
                SequentialAnimation on color {
                    loops: Animation.Infinite
                    ColorAnimation { from: "#14148c"; to: "#0E1533"; duration: 500000 }
                    ColorAnimation { from: "#0E1533"; to: "#14148c"; duration: 500000 }
                }
            }
            GradientStop {
                position: 1.0
                SequentialAnimation on color {
                    loops: Animation.Infinite
                    ColorAnimation { from: "#14aaff"; to: "#437284"; duration: 500000 }
                    ColorAnimation { from: "#437284"; to: "#14aaff"; duration: 500000 }
                }
            }
        }
    }

    // the sun, moon, and stars
    Item {
        width: parent.width; height: 2 * parent.height
        NumberAnimation on rotation { from: 0; to: 360; duration: 1000000; loops: Animation.Infinite }
        Image {
            source: "sun.png"; y: 10; anchors.horizontalCenter: parent.horizontalCenter
            rotation: -3 * parent.rotation
        }
        Image {
            source: "moon.png"; y: parent.height - 74; anchors.horizontalCenter: parent.horizontalCenter
            rotation: -parent.rotation
        }
        ParticleSystem {
            id: particlesystem
            x: 0; y: parent.height/2
            width: parent.width; height: parent.height/2
            ImageParticle {
                source: "star.png"
                groups: ["star"]
                color: "#00333333"
                SequentialAnimation on opacity {
                    loops: Animation.Infinite
                    NumberAnimation { from: 0; to: 1; duration: 500000 }
                    NumberAnimation { from: 1; to: 0; duration: 500000 }
                }
            }
            Emitter {
                group: "star"
                anchors.fill: parent
                emitRate: parent.width / 50
                lifeSpan: 5000
            }
        }
    }

    // ...and the ground.
    Rectangle {
        anchors { left: parent.left; top: parent.verticalCenter; right: parent.right; bottom: parent.bottom }
        gradient: Gradient {
            GradientStop {
                position: 0.0
                SequentialAnimation on color {
                    loops: Animation.Infinite
                    ColorAnimation { from: "#80c342"; to: "#001600"; duration: 500000 }
                    ColorAnimation { from: "#001600"; to: "#80c342"; duration: 500000 }
                }
            }
            GradientStop { position: 1.0; color: "#006325" }
        }
    }
    Flipable{
        id: flipable_
        anchors.bottomMargin: parent.height/2.5
        anchors.leftMargin: parent.width/2.5
        anchors.rightMargin: parent.width/2.5
        anchors.topMargin: parent.height/2.5
        anchors.bottom:  parent.bottom
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        property bool flipped: false

        transform: Rotation {
            id: rotationB
            origin.x: flipable_.width/2
            origin.y: flipable_.height/2
            axis.x: 0; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
            angle: 0    // the default angle
        }

        states: State {
            name: "back"
            PropertyChanges { target: rotationB; angle: 180 }
            when: flipable_.flipped
        }

        transitions: Transition {
            NumberAnimation { target: rotationB; property: "angle"; duration: 2000;easing.type: Easing.InOutQuad }
        }

       front: Image {
           width : parent.parent.width/8
           height: parent.parent.height/7.5
           source: "qrc:/client/games/BigKingsCup/pictures/VerdeckteKarte.png";
           anchors.rightMargin: -parent.width/2.5
           anchors.bottom:  parent.bottom
           anchors.top: parent.top
           anchors.right: parent.right
       }
        back:Image {
            id:imagefront
            width : parent.parent.width/8
            height: parent.parent.height/7.5
            anchors.leftMargin: -parent.width/2.5
            anchors.bottom:  parent.bottom
            anchors.top: parent.top
            anchors.left: parent.right
        }
    }

    Item{
        anchors.fill: parent
        Image {
            id:staticCard
            width : parent.parent.width/8
            height: parent.parent.height/7.5
                   source: "qrc:/client/games/BigKingsCup/pictures/VerdeckteKarte.png";
                   anchors.bottomMargin: parent.height/2.5
                   anchors.rightMargin: parent.width/3.15
                   anchors.topMargin: parent.height/2.5
                   anchors.bottom:  parent.bottom
                   anchors.top: parent.top
                   anchors.right: parent.right
               }
        Image {
            width : parent.parent.width/8
            height: parent.parent.height/7.5
                   source: "qrc:/client/games/BigKingsCup/pictures/VerdeckteKarte.png";
                   anchors.bottomMargin: parent.height/2.5
                   anchors.rightMargin: parent.width/3.125
                   anchors.topMargin: parent.height/2.5
                   anchors.bottom:  parent.bottom
                   anchors.top: parent.top
                   anchors.right: parent.right
               }
        Timer {
            id:sendOrderTimer
            interval:1000
            onTriggered: {
                ReadInformationFile.readFile("BigKingsCup/gameInformationFiles/"+KingsCupFunktions.sInfo[1]+".txt")
                ruleInformationTxt.sLastInfotext=ReadInformationFile.string
                ruleInformationTxt.state = "EXPANDED"
                sendOrderTimer.stop();
            }
        }
        MouseArea {
            anchors.fill: staticCard
            onClicked:{
                flipable.flipped = !flipable.flipped
                flipable_.flipped = !flipable.flipped
                KingsCupFunktions.nextCard()

                if (ruleInformationTxt.state === "EXPANDED")
                {
                    ReadInformationFile.readFile("BigKingsCup/gameInformationFiles/"+KingsCupFunktions.sInfo[0]+".txt")
                    ruleInformationTxt.sInfotext=ReadInformationFile.string
                    ruleInformationTxt.state = "HIDDEN"
                    sendOrderTimer.start()
                }
                else
                {
                    ReadInformationFile.readFile("BigKingsCup/gameInformationFiles/"+KingsCupFunktions.sInfo[0]+".txt")
                    console.log("Expanded infoString "+ReadInformationFile.string)
                    ruleInformationTxt.state = "EXPANDED"
                    ruleInformationTxt.sLastInfotext=ReadInformationFile.string
                }
            } //!flipable.flipped
        }
    }


    Flipable{
        id: flipable
        anchors.bottomMargin: parent.height/2.5
        anchors.leftMargin: parent.width/2.5
        anchors.rightMargin: parent.width/2.5
        anchors.topMargin: parent.height/2.5
        anchors.bottom:  parent.bottom
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        property bool flipped: false

        transform: Rotation {
            id: rotation
            origin.x: flipable.width/2
            origin.y: flipable.height/2
            axis.x: 0; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
            angle: 0    // the default angle
        }

        states: State {
            name: "back"
            PropertyChanges { target: rotation; angle: -180 }
            when: flipable.flipped
        }

        transitions: Transition {
            NumberAnimation { target: rotation; property: "angle"; duration: 2000;easing.type: Easing.InOutQuad }
        }

        front  : Image {
           width : parent.parent.width/8
           height: parent.parent.height/7.5
           source: "qrc:/client/games/BigKingsCup/pictures/VerdeckteKarte.png";
           anchors.rightMargin: -parent.width/2.5
           anchors.bottom:  parent.bottom
           anchors.top: parent.top
           anchors.right: parent.right
       }
        back:Image {
            id:imageBack
            width : parent.parent.width/8
            height: parent.parent.height/7.5
            anchors.leftMargin: -parent.width/2.5
            anchors.bottom:  parent.bottom
            anchors.top: parent.top
            anchors.left: parent.right
        }
    }

    Information{
    id:ruleInformationTxt
    }


    CloseButton{

    }

}
