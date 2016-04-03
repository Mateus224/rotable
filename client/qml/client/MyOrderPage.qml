import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    color: "#00000000"


    MouseArea {
        id: idMouseAreaBProductPage
        anchors.fill: parent
        enabled: true
    }

    Queue{
        id: queue
    }

    Rectangle {
        id: categoryTitle

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: parent.height * 0.1
        width: parent.width //* 0.33333
        height: parent.height * 0.05
        gradient: clubcolorsrevers
        Gradient {
            id: clubcolorsrevers
            GradientStop { position: 0.0; color:"#8EE2FE"}//"#8EE2FE"}
            GradientStop { position: 0.90; color: "#000000"}
        }
        /*Image {
            anchors.fill: parent
            source: "qrc:/client/resources/TopBarLeft.png"
        }*/

        Text {
            id: categoryTitleLabel
            text: "My Order"
            font.family: "FreeSans"
            color: "#000000"
            font.bold: true
            font.pixelSize: parent.height * 0.8
            anchors.verticalCenter: parent.verticalCenter
            //anchors.left: parent.left
            //anchors.leftMargin: parent.width * 0.1
            anchors.centerIn: parent
            font.capitalization: Font.AllUppercase
        }
    }

    MyOrderButton {
        id: buttonMyOrder
    }

    /*Image {
        id: logo
        source: "qrc:/client/resources/rotable_logo.png"

        anchors.top: categoryBar.bottom
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        //anchors.right: parent.right
        anchors.margins: 10

        fillMode: Image.PreserveAspectFit
    }*/


    CategoryBar {
        id: categoryBar
    }

    MyOrderRects {
        id: myOrderRects
        }

}


