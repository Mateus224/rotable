import QtQuick 2.0
import QtMultimedia 5.0
import "qrc:componentCreation.js" as CreateComponent

    Rectangle{
         id:table
         width:700
         height:400
         color: "#ffffff"

         Component.onCompleted: CreateComponent.createSpriteObjects();


          /*  Rectangle {
                id: rectangle1
                x: 20
                y: 100
                width: 177
                height: 81
                color: "#11ffff"
                MouseArea{
                   id: buttonMouseArea1

                   anchors.fill: parent //anchor all sides of the mouse area to the rectangle's anchors
                   //onClicked handles valid mouse button clicks
                   onClicked: console.log(" clicked" )
                }

                Text {
                    id: name0
                    text: qsTr("Tisch 1")

                font.pointSize: 10
                anchors.centerIn: parent
                }
            }

                Rectangle {
                    id: rectangle2
                    x: 20
                    y: 200
                    width: 177
                    height: 81
                    color: "#11ffff"
                    MouseArea{
                       id: buttonMouseArea2

                       anchors.fill: parent //anchor all sides of the mouse area to the rectangle's anchors
                       //onClicked handles valid mouse button clicks
                       onClicked: console.log(" clicked" )
                }
                    Text {
                        id: name
                        text: qsTr("Tisch 3")

                    font.pointSize: 10
                    anchors.centerIn: parent
                    }

            }



                Rectangle {
                    id: rectangle3
                    x: 20
                    y: 300
                    width: 177
                    height: 81
                    color: "#11ffff"
                    MouseArea{
                       id: buttonMouseArea3

                       anchors.fill: parent //anchor all sides of the mouse area to the rectangle's anchors
                       //onClicked handles valid mouse button clicks
                       onClicked: console.log(" clicked" )

                    }

                    Text {
                        id: name1
                        text: qsTr("Tisch 3")

                    font.pointSize: 10
                    anchors.centerIn: parent
                    }


                }

*/



function createSpriteObjects() {
    component = Qt.createComponent("Sprite.qml");
    sprite = component.createObject(appWindow, {"x": 100, "y": 100});

    if (sprite == null) {
        // Error Handling
        console.log("Error creating object");
    }
}
}
