import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import "KingsCupFunktions.js" as KingsCupFunktions

Rectangle {
    id:gameLost
    y:-2* parent.height/5
    anchors.left: parent.left
    anchors.right: parent.right
    width: parent.width
    height:2* parent.height/5
    property int stateChangeDuration: 5000
    color: "black"
    property string sInfotext : ""
    property string sLastInfotext : ""
    state: "HIDDEN"
    visible:false


    TextArea{
        id:gameLostText
        textFormat:TextEdit.RichText
        //backgroundVisible: false
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: screen.height/10
        anchors.bottomMargin: screen.height/10
        anchors.leftMargin: screen.width/10
        anchors.rightMargin: screen.width/10
        text: "<center> Verloren ! !</center> Du hast den dritten König gezogen !<blockquote></blockquote> Viel Spaß beim Exen !"
        font.family: "FreeSans"
        //color:  "white"
        font.bold: true
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
                PropertyChanges { target: gameLost; y: 2*parent.height/5}
                PropertyChanges { target: gameLost; z: 1 }
            },
            State {
                name: "HIDDEN"
                PropertyChanges { target: gameLost; visible: false }
                PropertyChanges { target: gameLost; z: 0 }
            }
        ]

}
