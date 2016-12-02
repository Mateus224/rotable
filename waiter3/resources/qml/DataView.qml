import QtQuick 2.5

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
            }
            PropertyChanges {
                target: notImp
                visible: false
            }
        },

        State {
            name: "NotImplemented"
            PropertyChanges {
                target: tablesView
                visible: false
            }
            PropertyChanges {
                target: notImp
                visible: true
            }
        }
    ]
}