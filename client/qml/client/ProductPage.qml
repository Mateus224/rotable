import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    color: "#00000000"


    MouseArea {
        id: idMouseAreaBProductPage
        anchors.fill: parent
        enabled: true
        onClicked: touchEvent.newTouchEvent()
    }

    Rectangle {
        id: categoryTitle

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: parent.height * 0.05
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
            text: client.currentCategoryName ? client.currentCategoryName: ""
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

    CategoryBar {
        id: categoryBar
    }

    ProductRects {
        id: productRects
    }
    Queue{

    }
}
