import QtQuick 2.0
import "SpinTheBottle/"

Rectangle {
    id: gameGridRectTemplate
    property int stateChangeDuration: 400
    property string gameName: ""
    property string infoString: ""
    property int id_: 15
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
        color: parent.color
        visible: false


        x: parent.x
        y: parent.y
        width: parent.width
        height: parent.height
        Text{
            anchors.fill: parent
            text: infoString
            font.family: "FreeSans"
            color: "#FFFFFFFF"
            font.bold: true
            font.pixelSize: parent.height * 0.05
            font.capitalization: Font.AllUppercase
            wrapMode: Text.Wrap
        }

        Rectangle{
            id: playGameButton
            color:"red"
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 3*parent.height/4
            Text{
                anchors.fill: parent
                text: "PLAY GAME"
                font.family: "FreeSans"
                color: "#FFFFFFFF"
                font.bold: true
                font.pixelSize: parent.height * 0.5
                font.capitalization: Font.AllUppercase
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            MouseArea{
                anchors.fill: parent
                onClicked:  {
                    switch (id_)
                    {
                    case 0:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "SPINTHEBOTTLE"
                        }
                        break
                    case 1:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "SPINTHEBOTTLE"
                        }
                        break
                    case 2:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "DEFAULT"
                        }
                        break
                    case 3:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "DEFAULT"
                        }
                        break
                    case 4:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "DEFAULT"
                        }
                        break
                    case 5:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "DEFAULT"
                        }
                        break
                    case 6:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "DEFAULT"
                        }
                        break
                    case 7:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "SPINTHEBOTTLE"
                        }
                        break
                    case 8:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "SPINTHEBOTTLE"
                        }
                        break
                    case 9:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "DEFAULT"
                        }
                        break
                    case 10:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "DEFAULT"
                        }
                        break
                    case 11:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "DEFAULT"
                        }
                        break
                    case 12:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "DEFAULT"
                        }
                        break
                    case 13:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "DEFAULT"
                        }
                        break
                    case 14:
                        if (gamePage.state == "DEFAULT")
                        {
                            gamePage.state = "DEFAULT"
                        }
                        break
                    }
                }
            }

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
        /*if (gamePage.state == "DEFAULT")
            {
                gamePage.state = "SPINTHEBOTTLE"
            }*/
        if (gameGridRectTemplate.state == "COLLAPSED")
        {
            gameGridRectTemplate.state = "EXPANDED"
        }


        }
    }


    states: [
        State {
            name: "EXPANDED"
            PropertyChanges { target: buttonExpanded; visible: true }
            PropertyChanges { target: buttonExpanded; x: -gameGridRectTemplate.x}
            PropertyChanges { target: buttonExpanded; y: -gameGridRectTemplate.y}
            PropertyChanges { target: buttonExpanded; width: 5 * (gridGamePage.width  * 0.015 + gameGridRectTemplate.buttonWidth ) - gameGridRectTemplate.buttonMarginH }
            PropertyChanges { target: buttonExpanded; height: 3 * (gridGamePage.height*0.025 + gameGridRectTemplate.buttonHeight)- gameGridRectTemplate.buttonMarginV }
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
