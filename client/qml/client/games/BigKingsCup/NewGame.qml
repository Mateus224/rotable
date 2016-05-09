import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import "KingsCupFunktions.js" as KingsCupFunktions

Rectangle {
    id:gameLost
    y:0
    anchors.left: parent.left
    anchors.right: parent.right
    width: parent.width
    height: parent.height/3
    property int stateChangeDuration: 400
    color: "black"
    property string sInfotext : ""
    property string sLastInfotext : ""
    state: "HIDDEN"
    visible:false


    TextArea{
        id:gameLostText
        textFormat:TextEdit.RichText
        backgroundVisible: false
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height/4
        text: "Du hast den vierten König gezogen viel Spaß beim Trinken des 6 cl Vodkas ;D"
        font.family: "FreeSans"
        textColor:  "white"
        font.bold: false
        font.pixelSize: parent.height * 0.08
        font.capitalization: Font.AllUppercase
        wrapMode: Text.Wrap
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

    MouseArea {
        id: idButtonGlobalMouseArea
        anchors.fill: parent
        enabled: true
        onClicked:  {
            if (gameLost.state === "EXPANDED")
            {
                gameLost.state = "HIDDEN"
            }
        }
    }

        states: [
            State {
                name: "EXPANDED"
                PropertyChanges { target: gameLost; visible: true }
                PropertyChanges { target: gameLost; y: parent.height/4}
                PropertyChanges { target: gameLost; z: 1 }
            },
            State {
                name: "HIDDEN"
                PropertyChanges { target: gameLost; visible: false }
                PropertyChanges { target: gameLost; z: 0 }
            }
        ]

    }
