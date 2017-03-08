import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.VirtualKeyboard 2.1

Rectangle {
    id: mainLayout
    color: "#00000000"

    property double dynamicSize: Math.min(parent.width * 0.07, parent.height * 0.12)
    property double buttonMargin: height * 0.015
    property double dynamicHeight: Math.max(70,parent.height * 0.1)
    property double fontSize: parent.height*0.035

    // Clear fields on state change
    onStateChanged: {
        passwordField.text = "";
    }

    Label {
        id: appname

        width: parent.width * 0.6
        height: parent.height * 0.12

        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.08
        anchors.horizontalCenter: parent.horizontalCenter

        text: qsTr("Rotable Waiter")+ langObject.emptyString

        font.pixelSize: dynamicSize
        style: Text.Outline
        font.family: "Times New Roman"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap

//        Behavior on anchors.topMargin { PropertyAnimation { easing.type: Easing.InOutQuad; duration: 250 } }
    }

    TextField {
        id: loginField
        width: Math.max(100,parent.width * 0.25)
        height: dynamicHeight
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: appname.bottom
        anchors.topMargin: parent.height * 0.06
        onTextChanged: waiter.login = text
        placeholderText: qsTr("Please insert login")+ langObject.emptyString
        font.pixelSize: fontSize

    }

    TextField {
        id: passwordField

        width: Math.max(250,parent.width * 0.25)
        height: dynamicHeight
        anchors.top: loginField.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        echoMode: 2
        onTextChanged: waiter.password = text
        placeholderText: qsTr("Please insert password")+ langObject.emptyString
        font.pixelSize: fontSize
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
                        PropertyChanges {
                            target: appname
                            anchors.topMargin: -appname.height
                        }
                        PropertyChanges {
                            target: loginField
                            anchors.topMargin: mainLayout.height * 0.015
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
                            NumberAnimation {
                                target: appname
                                properties: "anchors.topMargin"
                                duration: 250
                                easing.type: Easing.InOutQuad
                            }
                            NumberAnimation {
                                target: loginField
                                properties: "anchors.topMargin"
                                duration: 250
                                easing.type: Easing.InOutQuad
                            }
                        }
                    }
    }

    Button {
        id: loginButton
        text: qsTr("Login") + langObject.emptyString

        anchors.left: loginField.left
        anchors.top: passwordField.bottom
        anchors.topMargin: buttonMargin
        //anchors.right: passwordField.horizontalCenter
        anchors.right:loginField.right
        height: dynamicHeight
        activeFocusOnPress: true
        isDefault: true
        onClicked: waiter.logIn()

        style: ButtonStyle {
            label: Text {
                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: "Helvetica"
                font.pixelSize: fontSize
                text: control.text
            }
        }
    }

/*    Button {
        id: closeButton
        text: qsTr("Close")+ langObject.emptyString

        anchors.right: loginField.right
        anchors.top: passwordField.bottom
        anchors.topMargin: buttonMargin
        anchors.left: passwordField.horizontalCenter

        height: dynamicHeight
        onClicked: Qt.quit()

        style: ButtonStyle {
            label: Text {
                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: "Helvetica"
                font.pointSize: control.width * 0.15
                text: control.text
            }
        }
    }*/

    Text {
        id: text1
        text: qsTr("Text")+ langObject.emptyString
        font.pixelSize: dynamicSize / 2
        opacity: 0

        anchors.top: loginButton.bottom
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
