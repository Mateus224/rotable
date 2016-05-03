import QtQuick 2.0
import "SpinTheBottle/"

Rectangle {
    id: gameGridRectTemplate
    property int stateChangeDuration: 400
    property string gameName: ""
    property string _center: ""
    property int buttonMarginH: parent.parent.width  * 0.015
    property int buttonMarginV: parent.parent.height * 0.025
    property int buttonWidth:  (parent.parent.width  - buttonMarginH) / 5.01 - buttonMarginH
    property int buttonHeight: (parent.parent.height - buttonMarginV) / 3.01 - buttonMarginV
    width: buttonWidth
    height: buttonHeight
    state: "COLLAPSED"

    Text{
        id:gameText
        anchors.fill: parent
        wrapMode: Text.Wrap
        font.family: "FreeSans"
        color: "#FFFFFFFF"
        font.bold: true
        font.pixelSize: parent.buttonHeight * 0.175
        anchors.centerIn: parent
        font.capitalization: Font.AllUppercase
        text: gameName
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

    }
    Rectangle {
        //anchors.verticalCenter: parent.verticalCenter
        //anchors.horizontalCenter: parent.horizontalCenter
        id: buttonExpanded
        SpinBottle{

        }

        Behavior on x {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on y {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on width {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on height {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on z {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
    }


    MouseArea {
        id: idButtonGlobalMouseArea
        anchors.fill: parent
        enabled: true
        onClicked:  {
        if (gamePage.state == "DEFAULT")
            {
                gamePage.state = "SPINTHEBOTTLE"

            }


        }
    }

    states: [
        State {
            name: "EXPANDED"
            PropertyChanges { target: buttonExpanded; visible: true }
            PropertyChanges { target: buttonExpanded; x: -Math.min(mainScreen.height, mainScreen.width)/2}
            PropertyChanges { target: buttonExpanded; y: -Math.min(mainScreen.height, mainScreen.width)/2}
            PropertyChanges { target: buttonExpanded; width: Math.min(mainScreen.height, mainScreen.width) }
            PropertyChanges { target: buttonExpanded; height: Math.min(mainScreen.height, mainScreen.width) }
            PropertyChanges { target: gameGridRectTemplate; z: 1 }
            PropertyChanges { target: buttonExpanded; z: 1 }
        },
        State {
            name: "COLLAPSED"
            PropertyChanges { target: buttonExpanded; visible: false }
            PropertyChanges { target: buttonExpanded; width: buttonWidth }
            PropertyChanges { target: buttonExpanded; height: buttonHeight }
            PropertyChanges { target: buttonExpanded; x: gameGridRectTemplate.x }
            PropertyChanges { target: buttonExpanded; y: gameGridRectTemplate.y }
            PropertyChanges { target: buttonExpanded; z: 0 }
            PropertyChanges { target: gameGridRectTemplate; z: 0}
        }
    ]

}
