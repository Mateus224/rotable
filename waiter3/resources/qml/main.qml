import QtQuick 2.5

import "LoadingView/"

Rectangle{
    visible: true
    id: mainscreen

    width: 1333
    height: 786

    WaiterView {
        id: waiterView
        anchors.fill: parent
        opacity: 0
    }

    LoginView {
        id: loginView
        y: 230
        anchors.fill: parent
        opacity: 0
    }

    Text {
        id: noConnectionText
        text: qsTr("Text")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: loadsymbol.bottom
        anchors.topMargin: loadsymbol.height
        font.pixelSize: 12
        visible: false
    }

    LoadingSymbol {
        id: loadsymbol
        anchors.centerIn: parent
        visible: false
    }

    state: waiter.state

    states: [

        State {
            name: "Login"

            PropertyChanges {
                target: loginView
                clip: false
                visible: true
                opacity: 1
            }
        },

        State {
            name: "WaiterView"

            PropertyChanges {
                target: waiterView
                opacity: 1
            }
        },

        State {
            name: "DISCONNECTED"

            PropertyChanges {
                target: noConnectionText
                text: qsTr("No connection, connecting...")
                font.pixelSize: 36
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                visible: true
            }

            PropertyChanges {
                target: loadsymbol
                visible: true
            }
        }
    ]

}
