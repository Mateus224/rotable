import QtQuick 2.0

Rectangle {
    width: (mainScreen.width-Math.min(parent.height, parent.width))/2
    height: mainScreen.height/2
    color: mainScreen.device()
    Rectangle{
        id:rect1
        anchors.fill: parent
        anchors.topMargin: parent.height * topMargin
        anchors.leftMargin: parent.width * Math.max(topMargin, bottomMargin)
        anchors.rightMargin: parent.width * Math.max(topMargin, bottomMargin)
        anchors.bottomMargin: parent.height * bottomMargin
        color:"black"
        MouseArea{
            anchors.fill: parent
            onReleased: screen.rotation= _rotation
        }
        /*Image {
            id: backgroundImage
            anchors.fill: parent
            //source: "qrc:/client/resources/bg_categories.png"
            rotation: _rotation
        }*/
    }
}
