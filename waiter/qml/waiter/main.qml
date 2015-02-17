import QtQuick 2.0
import QtMultimedia 5.0
import "componentCreation.js" as CreateComponent


Rectangle {
    id: appWindow
    width: 900; height: 600
    color:"#800000FF"

    //TableButton{}

    TableGrid{}
    Rectangle{

        id: tableWindow

         width: 200; height: parent.height
         color:"#80000000"

         TestQml{

         }
/*
        ListModel {
            id: myModel
            ListElement { name: "Table 1"
                          cost: 0
                          surfaceColor: "transparent"
                          color: "transparent"
                           }
            ListElement { name: "Table 2"
                          cost: 0
                          surfaceColor: "red"
                          }
        }*/
        Component {
            id: nameDelegate
            Text {
                text: name+" "+cost
                font.pixelSize: 24
            }
        }




        ListView {
            anchors.fill: parent
            clip: true
            model: myModel
            //delegate: nameDelegate
            header: bannercomponent
            footer: Rectangle {
                width: parent.width; height: 30;
                gradient: clubcolors
            }
            highlight: Rectangle {
                    color: "lightblue"
                    width: parent.width
                }
            delegate:Component {
                Item {
                    id: container
                    width: ListView.view.width; height: 60; anchors.leftMargin: 10; anchors.rightMargin: 10
                    property bool incoming_order: false

                    Rectangle {
                        id: content
                        anchors.centerIn: parent; width: container.width - 40; height: container.height - 10

                        //color:{ if (incoming_order) "blue"; else "transparent" }
                        antialiasing: true
                        radius: 10
                        //border.color: "black"
                        border.width: 1
                        color: model.modelData.color //surfaceColor

                        Rectangle { anchors.fill: parent; anchors.margins: 3; color: "#899AAEE0"; antialiasing: true; radius: 8 }
                    }

                    Text {
                        id: label
                        anchors.centerIn: content
                        text: name//"Table " + (index + 1)
                        color: "#EEEFFEFFE"
                        font.pixelSize: 14
                    }

                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true

                        onClicked: {
                            container.ListView.view.currentIndex = index
                            container.forceActiveFocus()
                        }
                    }
                }

            }

        }

        Component {     //instantiated when header is processed
            id: bannercomponent
            Rectangle {
                id: banner
                width: parent.width; height: 50
                gradient: clubcolors
                border {color: "#9EDDF2"; width: 2}
                Text {
                    anchors.centerIn: parent
                    text: "Tables"
                    font.pixelSize: 32
                }
            }
        }
        Gradient {
            id: clubcolors
            GradientStop { position: 0.0; color: "#8EE2FE"}
            GradientStop { position: 0.66; color: "#7ED2EE"}
        }
    }

}
