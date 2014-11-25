import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    color: "#00000000"

    Rectangle {
        id: categoryTitle
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 10
        color: "#00000000"

        width: 250
        height: 75

        Image {
            id: categoryTitleBackground
            anchors.fill: parent
            source: "qrc:/client/resources/bg_title.png"
            antialiasing: true
        }

        Text {
            id: categoryTitleLabel
            text: client.currentCategoryName
            font.family: "FreeSans"
            color: "#000000"
            font.pointSize: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 15
            font.capitalization: Font.AllUppercase
        }
    }

    MyOrderButton {
        id: buttonMyOrder
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 20
    }

    Image {
        id: logo
        source: "qrc:/client/resources/rotable_logo.png"

        anchors.top: categoryBar.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 5

        fillMode: Image.PreserveAspectFit
    }

    CategoryBar {
        id: categoryBar
    }

    ProductRects {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
