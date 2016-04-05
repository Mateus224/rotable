import QtQuick 2.0

Rectangle {
    width: (mainScreen.width-Math.min(parent.height, parent.width))/2
    height: mainScreen.height/2
    color: mainScreen.color="black"
    Rectangle{
        id:rect1
        anchors.fill: parent
        //anchors.topMargin: parent.height * topMargin
        //anchors.leftMargin: parent.width * Math.max(topMargin, bottomMargin)
        //anchors.rightMargin: parent.width * Math.max(topMargin, bottomMargin)
        //anchors.bottomMargin: parent.height * bottomMargin
        color:"black"
        function device(){
            var device
            if(client.device_===1)
                device= "qrc:/client/resources/Pfeil_01.png"
            else
                device= "black"
            return device
        }

        Image {
            id: backgroundImage
            anchors.centerIn: parent
            width: parent.width/2
            height: parent.width/2
            source: rect1.device()
            rotation: _rotation+90
            MouseArea{
                anchors.fill: parent
                onPressed: parent.source= "qrc:/client/resources/Pfeil_02.png"
                onReleased:{
                    screen.rotation= _rotation
                    parent.source=   "qrc:/client/resources/Pfeil_01.png"
                }
            }
        }

    }
}
