import QtQuick 2.0

Rectangle {
    anchors.top: parent.top
    anchors.right: parent.right
    anchors.topMargin: parent.height * 0.1
    width: parent.width * 0.33333
    height: parent.height * 0.05
    color: "#00000000"

    Image {
        anchors.fill: parent
        source: "qrc:/client/resources/TopBarRight.png"
        antialiasing: true
    }
    property string myorderscreen: "MYORDERSCREEN"
    MouseArea {
        id:te
        anchors.fill: parent
        onClicked: {
            client.state= myorderscreen
            MyOrder.getListForMyOrderPage()
        }



    }

    Text {
        id: buttonLabel
        text: "MY ORDER"
        font.family: "FreeSans"
        color: "#ffffff"
        font.bold: true
        font.pixelSize: parent.height * 0.8
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: parent.width * 0.1
    }
}
