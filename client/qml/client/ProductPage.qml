import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    color: "#00000000"


    MouseArea {
        id: idMouseAreaBProductPage
        anchors.fill: parent
        enabled: true
    }

    Rectangle {
        id: categoryTitle

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: parent.height * 0.1
        width: parent.width * 0.33333
        height: parent.height * 0.05
        color: "#00000000"

        Image {
            anchors.fill: parent
            source: "qrc:/client/resources/TopBarLeft.png"
        }

        Text {
            id: categoryTitleLabel
            text: client.currentCategoryName
            font.family: "FreeSans"
            color: "#000000"
            font.bold: true
            font.pixelSize: parent.height * 0.8
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            font.capitalization: Font.AllUppercase
        }
    }

    MyOrderButton {
        id: buttonMyOrder
    }

    Image {
        id: logo
        source: "qrc:/client/resources/rotable_logo.png"

        anchors.top: categoryBar.bottom
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        //anchors.right: parent.right
        anchors.margins: 10

        fillMode: Image.PreserveAspectFit
    }

    CategoryBar {
        id: categoryBar
    }
    /*
    Image {
        property int buttonSizeH: parent.height * 0.1
        property int buttonSizeW: ( parent.height*0.01)

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenterOffset: buttonSizeW
        anchors.bottomMargin: parent.height * 0.125

        //height: parent.height * 0.1
        id: logo
        source: "qrc:/client/resources/rotable_logo.png"
         //:buttonSizeW
        //anchors.bottom: categoryBar.top

        anchors.horizontalCenter: parent.horizontalCenter
        //anchors.margins: 10

        height : buttonSizeH
        fillMode: Image.PreserveAspectFit
    }
*/
    ProductRects {
        id: productRects
    }
}
