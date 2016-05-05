import QtQuick 2.5
import QtQuick.Particles 2.0
import "../SpinTheBottle/"

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
        id: flipable
        width: 360
        height: 360
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
            PropertyChanges { target: rotation; angle: 180 }
            when: flipable.flipped
        }

        transitions: Transition {
            NumberAnimation { target: rotation; property: "angle"; duration: 4000 }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: flipable.flipped = !flipable.flipped
        }


        anchors.bottom:  parent.bottom
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
       front: Image {
           source: "qrc:/client/games/BigKingsCup/Bilder/VerdeckteKarte.png";
           anchors.bottomMargin: parent.height/2.5
           anchors.leftMargin: parent.width/1.9
           anchors.rightMargin: parent.width/2.9
           anchors.topMargin: parent.height/2.5
           anchors.bottom:  parent.bottom
           anchors.top: parent.top
           anchors.left: parent.left
           anchors.right: parent.right
           //anchors.centerIn: parent.Center
       }
        back:Image {
            width: parent.width/9
            height: parent.height/6
            anchors.bottomMargin: parent.height/2.5
            anchors.leftMargin: parent.width/1.9
            anchors.rightMargin: parent.width/2.9
            anchors.topMargin: parent.height/2.5
            anchors.bottom:  parent.bottom
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            source: "qrc:/client/games/BigKingsCup/Bilder/10.png";

        }

    }








    CloseButton{

    }

}
