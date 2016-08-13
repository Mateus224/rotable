import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle{
    visible: true


    property int margin: 10
    width: 1333
    height: 786
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#ffffff"
        }

        GradientStop {
            position: 1
            color: "#000000"
        }
    }

    WaiterView {
        id: waiterView1
        anchors.fill: parent
        opacity: 0
    }

    LoginView {
        id: loginView1
        y: 230
        anchors.fill: parent
        opacity: 0
    }

    Text {
        id: text1
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
                target: loginView1
                clip: false
                visible: true
                opacity: 1
            }
        },
        State {
            name: "WaiterView"

            PropertyChanges {
                target: waiterView1
                anchors.rightMargin: 8
                anchors.bottomMargin: 8
                anchors.leftMargin: 12
                anchors.topMargin: 12
                opacity: 1
            }
        },
        State {
            name: "DISCONNECTED"

            PropertyChanges {
                target: text1
                text: qsTr("No connection, connectiong...")
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                font.pixelSize: 36
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                opacity: 1
            }
        }
    ]

}
