import QtQuick 2.5
import QtGraphicalEffects 1.0

Rectangle {

    id: timeBarLayout

    width: parent.width
    height: Math.max(20,parent.height * 0.06)
    anchors.top: parent.top

    state: "Normal"

    Rectangle {
        id: rotableLogo
        anchors.left: parent.left
        anchors.right: clock.left
        height: parent.height

        Image {
            id:logoImage
            source: "qrc:/resources/images/rotable_logo.png"
            fillMode: Image.PreserveAspectFit
            anchors.left: parent.left
            height: parent.height
            anchors.bottomMargin: 5
            anchors.leftMargin: 5
            anchors.bottom: parent.bottom
        }

        DropShadow {
            anchors.fill: logoImage
            horizontalOffset: 3
            verticalOffset: 3
            radius: 10
            samples: 21
            color: "#a0000000"
            source: logoImage
        }
    }

    SimpleClock {
        id: clock
    }

    Rectangle {
        id: userName

        anchors.right: parent.right
        anchors.left: clock.right
        anchors.rightMargin: parent.width * 0.02
        height: parent.height

        Text {
            text: waiter.login
            font.pixelSize: parent.height * 0.6
            anchors.centerIn: parent
        }
    }

    MouseArea{
        anchors.fill: parent
//        onClicked: {
//            if (timeBarLayout.state=="Success") timeBarLayout.state="Fail"
//            else if (timeBarLayout.state=="Fail") timeBarLayout.state="Normal"
//            else if (timeBarLayout.state=="Normal") timeBarLayout.state="Success"
//        }
    }

    states: [

        State {
            name: "Success"

            PropertyChanges {
                target: timeBarLayout
                color: "#00FF00"
            }
            PropertyChanges {
                target: clock
                color: "#00FF00"
            }
            PropertyChanges {
                target: userName
                color: "#00FF00"
            }
        },

        State {
            name: "Fail"

            PropertyChanges {
                target: timeBarLayout
                color: "#FF0000"
            }
            PropertyChanges {
                target: clock
                color: "#FF0000"
            }
            PropertyChanges {
                target: userName
                color: "#FF0000"
            }
        },

        State {
            name: "Normal"

            PropertyChanges {
                target: timeBarLayout
                color: "#FFFFFF"
            }
            PropertyChanges {
                target: clock
                color: "#FFFFFF"
            }
            PropertyChanges {
                target: userName
                color: "#FFFFFF"
            }
        }
    ]
}
