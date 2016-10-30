import QtQuick 2.5
import QtQuick.Controls 1.4

Rectangle {
    id: mainLayout
    color: "#00000000"

    // Clear fields on state change
    onStateChanged: {
//        textField1.text = "";
        textField2.text = "";
    }

    Button {
        id: loginButton
        y: 215
        text: qsTr("Log in") + langObject.emptyString
        anchors.leftMargin: 0
        anchors.left: textField1.left
        checkable: false
        activeFocusOnPress: true
        isDefault: true
        onClicked: waiter.logIn()
    }

    Label {
        id: label1
        x: 77
        y: 89
        width: 486
        height: 17
        text: qsTr("Rotable Waiter Application")+ langObject.emptyString
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 22
        style: Text.Outline
        font.family: "Times New Roman"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
    }

    Button {
        id: closeButton
        x: 342
        y: 215
        text: qsTr("Close")+ langObject.emptyString
        anchors.right: textField1.right
        onClicked: Qt.quit()
    }

    TextField {
        id: textField1
        x: 218
        y: 130
        width: 204
        height: 33
        anchors.horizontalCenter: label1.horizontalCenter
        onTextChanged: waiter.login = text
        placeholderText: qsTr("Please insert login")+ langObject.emptyString
    }

    TextField {
        id: textField2
        x: 213
        y: 178
        width: 204
        height: 31
        anchors.horizontalCenter: label1.horizontalCenter
        echoMode: 2
        onTextChanged: waiter.password = text
        placeholderText: qsTr("Please insert password")+ langObject.emptyString
    }

    Text {
        id: text1
        y: 290
        text: qsTr("Text")+ langObject.emptyString
        font.pixelSize: 12
        opacity: 0
    }

    state: waiter.loginViewState

    states: [
        State {
            name: "WrongLogin"

            PropertyChanges {
                target: text1
                x: 534
                y: 288
                width: 278
                height: 34
                text: qsTr("Wrong login or password")+ langObject.emptyString
                anchors.leftMargin: 0
                anchors.rightMargin: 1184
                font.pixelSize: 22
                opacity: 1
            }
        }
    ]



}
