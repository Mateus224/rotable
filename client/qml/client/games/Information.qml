import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import "ReadInformationFile.js" as ReadInformationFile
Rectangle {
    id:windowInfoText
    y:parent.height
    anchors.left: parent.left
    anchors.right: parent.right
    width: parent.width
    height: parent.height/3
    property int stateChangeDuration: 400
    color: "black"
    state: "HIDDEN"
    property string sInfotext : ""
    property string sLastInfotext : ""


    TextArea{
        id:gameInfoText
        textFormat:TextEdit.RichText
        backgroundVisible: false
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height/4
        text: sInfotext
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
            if (windowInfoText.state == "HIDDEN")
            {
                windowInfoText.state = "EXPANDED"
            }
        }
    }

        states: [
            State {
                name: "EXPANDED"
                PropertyChanges { target: windowInfoText; visible: true }
                PropertyChanges { target: windowInfoText; y: 3*parent.height/4}
                PropertyChanges { target: windowInfoText; z: 1 }
                PropertyChanges { target: gameInfoText; text: sInfotext}
            },
            State {
                name: "HIDDEN"
                PropertyChanges { target: windowInfoText; visible: true }
                PropertyChanges { target: windowInfoText; z: 0 }
                PropertyChanges { target: gameInfoText; text:sLastInfotext}
            }
        ]

    }

