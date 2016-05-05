import QtQuick 2.4


import QtQuick 2.0
import QtQuick.Particles 2.0

Item {
    id: window
    width: 320; height: 480

    // Let's draw the sky...
    Rectangle {
        anchors { left: parent.left; top: parent.top; right: parent.right; bottom: parent.verticalCenter }
        gradient: Gradient {
            GradientStop {
                position: 0.0
                SequentialAnimation on color {
                    loops: Animation.Infinite
                    ColorAnimation { from: "#14148c"; to: "#0E1533"; duration: 50000 }
                    ColorAnimation { from: "#0E1533"; to: "#14148c"; duration: 50000 }
                }
            }
            GradientStop {
                position: 1.0
                SequentialAnimation on color {
                    loops: Animation.Infinite
                    ColorAnimation { from: "#14aaff"; to: "#437284"; duration: 50000 }
                    ColorAnimation { from: "#437284"; to: "#14aaff"; duration: 50000 }
                }
            }
        }
    }

    // the sun, moon, and stars
    Item {
        width: parent.width; height: 2 * parent.height
        NumberAnimation on rotation { from: 0; to: 360; duration: 100000; loops: Animation.Infinite }
        Image {
            source: "sun.png"; y: 10; anchors.horizontalCenter: parent.horizontalCenter
            rotation: -3 * parent.rotation
        }
        Image {
            source: "imoon.png"; y: parent.height - 74; anchors.horizontalCenter: parent.horizontalCenter
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
                    NumberAnimation { from: 0; to: 1; duration: 50000 }
                    NumberAnimation { from: 1; to: 0; duration: 50000 }
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
                    ColorAnimation { from: "#80c342"; to: "#001600"; duration: 50000 }
                    ColorAnimation { from: "#001600"; to: "#80c342"; duration: 50000 }
                }
            }
            GradientStop { position: 1.0; color: "#006325" }
        }
    }

    Item{
        anchors.centerIn: parent.Center
        width: parent.width/4
        height: parent.height/4
        Image {
            anchors.centerIn: parent.Center
            source: "qrc:/client/games/BigKingsCup/Bilder/10.png"; y: 10; anchors.horizontalCenter: parent.horizontalCenter

        }
        Image {
            //source: "sun.png"; y: 10; anchors.horizontalCenter: parent.horizontalCenter
        }

    }
}
