import QtQuick 2.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.3
import QtQuick.Extras 1.4
import QtGraphicalEffects.private 1.0

ApplicationWindow{
    id: applicationWindow1
    visible: true
    title: qsTr("Waiter client")
    color: "#7AAEEE"

    ColumnLayout {
        id: columnLayout1
        x: 138
        y: 100
        width: 365
        height: 177
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Label {
            id: label1
            text: qsTr("Login")
            Layout.fillWidth: true
        }

        TextField {
            id: textField1
            text: qsTr("Text Field")
            Layout.fillWidth: true
        }

        Label {
            id: label2
            text: qsTr("Password")
            Layout.fillWidth: true
        }

        TextField {
            id: textField2
            x: 127
            y: 113
            text: qsTr("Text Field")
            Layout.fillWidth: true
        }

        Button {
            id: button3
            width: 209
            height: 40
            text: qsTr("Log in")
            visible: true
            Layout.fillWidth: true
        }







    }
}
