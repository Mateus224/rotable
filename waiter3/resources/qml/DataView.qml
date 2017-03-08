import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "TablesView/"

Rectangle {

    id: dataMain

    state: "Tables"

    property int leftMenuWidth

    TablesView {
        id: tablesView

        anchors.topMargin: 10
        anchors.fill: parent
    }

    Rectangle {
        id: logoutView

        anchors.topMargin: 10
        anchors.fill: parent

        property double fontSize: parent.height*0.035

        Button {
            id: logoutButton
            text: qsTr("Logout") + langObject.emptyString

            anchors.centerIn: parent
            height: parent.height * 0.2
            width: parent.width * 0.2
            activeFocusOnPress: true
            isDefault: true
            onClicked:
            {
                waiter.logOff()
                mainscreen.state=="Login"
            }

            style: ButtonStyle {
                label: Text {
                    renderType: Text.NativeRendering
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.family: "Helvetica"
                    font.pixelSize: logoutView.fontSize
                    text: control.text
                }
            }
        }
    }

    Rectangle {
        id:notImp

        anchors.topMargin: 10
        anchors.fill: parent

        Text {
            text: qsTr("Not availible yet") + langObject.emptyString
            anchors.centerIn: parent
            font.pixelSize: parent.height * 0.1
        }
    }

    states: [
        State {
            name: "Tables"
            PropertyChanges {
                target: tablesView
                visible: true
                enabled: true
            }
            PropertyChanges {
                target: logoutView
                visible: false
                enabled: false
            }
            PropertyChanges {
                target: notImp
                visible: false
                enabled: false
            }
        },

        State {
            name: "Logout"
            PropertyChanges {
                target: tablesView
                visible: false
                enabled: false
            }
            PropertyChanges {
                target: logoutView
                visible: true
                enabled: true
            }
            PropertyChanges {
                target: notImp
                visible: false
                enabled: false
            }
        },

        State {
            name: "NotImplemented"
            PropertyChanges {
                target: tablesView
                visible: false
                enabled: false
            }
            PropertyChanges {
                target: logoutView
                visible: false
                enabled: false
            }
            PropertyChanges {
                target: notImp
                visible: true
                enabled: true
            }
        }
    ]
}
