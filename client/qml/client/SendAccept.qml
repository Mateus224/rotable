import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    color: "#00000000"


    MouseArea {
        id: idMouseAreaPayedPage
        anchors.fill: parent
        enabled: true
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


        Text {
            id: categoryTitleLabel
            text: "SENT"
            font.family: "FreeSans"
            color: "#000000"
            font.bold: true
            font.pixelSize: parent.height * 0.8
            anchors.verticalCenter: parent.verticalCenter
            anchors.centerIn: parent
            anchors.leftMargin: parent.width * 0.1
            font.capitalization: Font.AllUppercase
        }
    }

    MyOrderButton {
        id: buttonMyOrder
    }

    Rectangle {
        anchors.fill: parent
        anchors.topMargin: (parent.height * 0.1)*3/2
        anchors.leftMargin: (parent.width * (1.0 - 0.805) / 2.0)*2/3*(1/2*0.82)
        anchors.rightMargin: (parent.width * (1.0 - 0.805) / 2.0)*2/3*(1/2*0.82)
        anchors.bottomMargin: (parent.height * (0.09125 + 0.10 + 0.125))*0.82
        color: "#3f494a"
        Rectangle {
            anchors.fill: parent
            anchors.margins: parent.height * 0.02

            color: "#000000"

            Text {
                id: tempText
                text: "Order was sent"
                font.family: "FreeSans"
                color: "#AAAAAA"
                font.bold: true
                font.pixelSize: parent.height * 0.1
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                font.capitalization: Font.AllUppercase
            }
        }
    }

    CategoryBar {
        id: categoryBar
    }
    Queue{

    }
}
