import QtQuick 2.0
import QtMultimedia 5.0
import "componentCreation.js" as CreateComponent


Rectangle {
    id: appWindow
    width: 900; height: 600
    color:"#800000FF"

    TableButton{
    }

        /*
        Text{
            text: "create Table"
            font.pixelSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
        */



    //Component.onCompleted: CreateComponent.createCategory();


}

