import QtQuick 2.0
import QtMultimedia 5.0
//import "componentCreation.js" as CreateComponent



Rectangle {
    id: appWindow
    width: 900; height: 600
    color:"#800000FF"

    //TableButton{}

    //TableGrid{}
    Rectangle {
        id:tableGrid
        width: 520
        height: 400
        x:250
        y:100
        color: "white"
        Component {
            id: contactDelegate
            Item {
                width: grid.cellWidth; height: grid.cellHeight
                Column {
                    anchors.fill: parent
                    //Image { source: portrait; anchors.horizontalCenter: parent.horizontalCenter }
                    Text { text: name; anchors.horizontalCenter: parent.horizontalCenter }
                }
            }
        }

        ListView {
            id:grid
            orientation: ListView.Vertical
            width: parent.width
            height: parent.height
            anchors.fill: parent
            clip: true
            model: table
            delegate: contactsDelegate


            Component {
                id: contactsDelegate
                Rectangle {
                    id: wrapper
                    width: grid.width
                    height: 50
                    //anchors.fill: parent

                    color: "transparent"

                    Row {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter

                            spacing: 5


                        Rectangle{

                            width:50
                            height:50
                            color: "transparent"


                            Text {
                                font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                                id: contactInfo
                                text:  pieces+"x"
                                color: newOrder

                            }
                        }

                        Rectangle{
                            width:150
                            height:50
                            color: "transparent"

                            Text {
                                font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                                id: contactInfoname
                                text:  orderName
                                color: newOrder
                            }
                        }
                        Rectangle{
                            width:50
                            height:50
                            color: "transparent"


                            Text {
                                font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                                id: contactInfoprice
                                text:  price.toFixed(2)+"€"
                                color: newOrder
                            }
                        }
                        Rectangle{
                            width:50
                            height:50
                            color: "transparent"


                            Text {
                                font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                                id: contactInfoready
                                text:  model.modelData.ready
                                color: newOrder
                            }
                        }
                        Rectangle{
                            width:50
                            height:50
                            color: "transparent"


                            Text {
                                font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                                id: contactInfoncancellation
                                text:  model.modelData.cancellation
                                color: newOrder
                            }
                        }
                        Rectangle{
                            width:50
                            height:50
                            color: "transparent"


                            Text {
                                font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                                id: contactInfontime
                                text:  1+" min"
                                color: newOrder
                            }
                        }
                    }
                }
            }



        }


    }
    Rectangle{

        id: tableWindow

         width: 200; height: parent.height
         color:"#80000000"


        Component {
            id: nameDelegate
            Text {
                text: name+" "+cost
                font.pixelSize: 24
            }
        }




        ListView {

            //currentIndex: curr
            anchors.fill: parent
            clip: true
            model: myModel
            //delegate: nameDelegate
            header: bannercomponent
            footer: Rectangle {
                width: parent.width; height: 50;
                gradient: clubcolors
            }
            highlight: Rectangle {
                    color: "lightblue"
                    width: 5//parent.width
                    //index:3
                }

            Connections{
                //target: myModel
                onChangeCurrentIndex: currentIndexT
            }

            delegate:Component {

                Item {
                    //id: item
                    signal qmlSignal(int msg)

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
                        text: "Table " + (index + 1)
                        color: CallWaiter//"White"
                        font.pixelSize: 14
                        font.bold: true
                    }

                    MouseArea {

                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true

                        onClicked: {
                            container.ListView.view.currentIndex = index
                            container.forceActiveFocus()
                            con.tableSlot(index + 1)
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
                    font.bold: true
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
