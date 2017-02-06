import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.VirtualKeyboard 2.1

Rectangle {
    id: mainLayout
    color: "#00000000"

    property double dynamicSize: Math.min(parent.width * 0.05, parent.height * 0.1)

    // Clear fields on state change
    onStateChanged: {
//        textField1.text = "";
        passwordField.text = "";
    }

    Label {
        id: appname

        width: parent.width * 0.4
        height: parent.height * 0.2

        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.08
        anchors.horizontalCenter: parent.horizontalCenter

        text: qsTr("Rotable Waiter Application")+ langObject.emptyString

        font.pixelSize: dynamicSize
        style: Text.Outline
        font.family: "Times New Roman"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
    }

    TextField {
        id: loginField
        width: Math.max(202,parent.width * 0.18)
        height: Math.max(38,parent.height * 0.029)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: appname.bottom
        anchors.topMargin: parent.height * 0.05
        onTextChanged: waiter.login = text
        placeholderText: qsTr("Please insert login")+ langObject.emptyString
    }

    TextField {
        id: passwordField

        width: Math.max(202,parent.width * 0.18)
        height: Math.max(38,parent.height * 0.029)
        anchors.top: loginField.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        echoMode: 2
        onTextChanged: waiter.password = text
        placeholderText: qsTr("Please insert password")+ langObject.emptyString
    }

    InputPanel {
        id: keyboard

        y: parent.height
        z:99
        anchors.left: parent.left
        anchors.right: parent.right
        active: true

        states: State {
                        name: "visible"
                        when: Qt.inputMethod.visible
                        PropertyChanges {
                            target: keyboard
                            y: parent.height - keyboard.height
                        }
                    }

        transitions: Transition {
                        from: ""
                        to: "visible"
                        reversible: true
                        ParallelAnimation {
                            NumberAnimation {
                                properties: "y"
                                duration: 250
                                easing.type: Easing.InOutQuad
                            }
                        }
                    }
    }

    Button {
        id: loginButton
        text: qsTr("Log in") + langObject.emptyString

        anchors.left: loginField.left
        anchors.top: passwordField.bottom
        anchors.topMargin: parent.height * 0.015
        anchors.right: passwordField.horizontalCenter
        checkable: false
        activeFocusOnPress: true
        isDefault: true
        onClicked: waiter.logIn()
    }

    Button {
        id: closeButton
        text: qsTr("Close")+ langObject.emptyString

        anchors.right: loginField.right
        anchors.top: passwordField.bottom
        anchors.topMargin: parent.height * 0.015
        anchors.left: passwordField.horizontalCenter
        onClicked: Qt.quit()
    }

    Text {
        id: text1
        text: qsTr("Text")+ langObject.emptyString
        font.pixelSize: dynamicSize / 2
        opacity: 0

        anchors.top: closeButton.bottom
        anchors.topMargin: parent.height * 0.02
        anchors.horizontalCenter: parent.horizontalCenter
    }

    state: waiter.loginViewState

    states: [
        State {
            name: "WrongLogin"

            PropertyChanges {
                target: text1
                text: qsTr("Wrong login or password")+ langObject.emptyString
                opacity: 1
            }
        }
    ]



}
