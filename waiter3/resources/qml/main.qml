import QtQuick 2.5

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
        anchors.fill: parent
        font.pixelSize: 12
        opacity: 0
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
                opacity: 1
            }
        }
    ]

}
