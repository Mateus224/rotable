import QtQuick 2.0
import "componentCreation.js" as CreateComponent


// http://qt-project.org/doc/qt-5/qtquick-statesanimations-animations.html
// http://qt-project.org/doc/qt-5/qtquick-modelviewsdata-modelview.html


Rectangle{

    id: tableWindow

     width: 200; height: 500
     color:"#80000000"

     TestQml{

     }

    ListModel {
        id: nameModel
        ListElement { name: "Table"
                      cost: 0
                      surfaceColor: "red"}
        ListElement { name: "Table"
                      cost: 0
                      surfaceColor: "black"}
    }
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
        model: nameModel
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
                    //signal clicked(color blue) //
                    //color:{ if (incoming_order) "blue"; else "transparent" }
                    antialiasing: true
                    radius: 10
                    //border.color: "black"
                    border.width: 1
                    color: surfaceColor

                    Rectangle { anchors.fill: parent; anchors.margins: 3; color: "#899AAEE0"; antialiasing: true; radius: 8 }
                }

                Text {
                    id: label
                    anchors.centerIn: content
                    text: "Table " + (index + 1)
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
