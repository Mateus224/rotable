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
        visible: false
        enabled: false
    }

    LoginView {
        id: loginView
        anchors.fill: parent
        visible: false
        enabled: false
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
        enabled: false
    }

    LoadingSymbol {
        id: loadsymbol
        anchors.centerIn: parent
        visible: false
        enabled: false
    }

    state: waiter.state

    states: [

        State {
            name: "Login"
            PropertyChanges {
                target: waiterView
                visible: false
                enabled: false
            }
            PropertyChanges {
                target: loginView
                clip: false
                visible: true
                enabled: true
            }
        },

        State {
            name: "WaiterView"

            PropertyChanges {
                target: waiterView
                visible: true
                enabled: true
            }
            PropertyChanges {
                target: loginView
                visible: false
                enabled: false
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
                enabled: true
            }

            PropertyChanges {
                target: loadsymbol
                visible: true
                enabled: true
            }
        }
    ]

}
