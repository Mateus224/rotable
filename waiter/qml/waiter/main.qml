import QtQuick 2.0
import QtMultimedia 5.0
//import "componentCreation.js" as CreateComponent



Rectangle {
    id: appWindow
    width: 900; height: 600
    color:"lightblue"//"#800000FF"

    //TableButton{}

    //TableGrid{}
    Rectangle {
        id:tableGrid
        width: 520
        height: 400
        x:250
        y:100
        color: "#7AAEEE"
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
            header: bannercomponentInfo


            Component {     //instantiated when header is processed
                id: bannercomponentInfo

                Rectangle {

                    id: banner
                    width: parent.width; height: 50
                    gradient: clubcolors
                    border {
                        color: "#9EDDF2";
                        width: 2}
                    Rectangle{
                        width:70
                        height:50
                        color: "transparent"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Pices"
                            font.pixelSize: 15
                            font.bold: true
                        }
                    }
                    Rectangle{
                        x:70
                        width:140
                        height:50
                        color: "transparent"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Order"
                            font.pixelSize: 15
                            font.bold: true
                        }
                    }

                }
            }

            Component {
                id: contactsDelegate
                Rectangle {
                    id: wrapper
                    width: grid.width
                    height: 50
                    color: "transparent"//"blue"


                    Row {

                            spacing: 5


                        Rectangle{
                            width:70
                            height:50
                            color: "lightblue" //"transparent"

                            Text {
                                font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                                id: contactInfo
                                text:  pieces+"x"
                                color: newOrder
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter

                            }
                        }

                        Rectangle{
                            width:150
                            height:50
                            color: "lightblue" //"transparent"

                            Text {
                                font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                                id: contactInfoname
                                text:  orderName
                                color: newOrder
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                        Rectangle{
                            width:50
                            height:50
                            color: "lightblue"


                            Text {
                                font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                                id: contactInfoprice
                                text:  price.toFixed(2)+"€"
                                color: newOrder
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                        Rectangle{
                            width:50
                            height:50
                            color: "lightblue"


                            Text {
                                font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                                id: contactInfoready
                                text:  model.modelData.ready
                                color: newOrder
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                        Rectangle{
                            width:50
                            height:50
                            color: "lightblue"


                            Text {
                                font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                                id: contactInfoncancellation
                                text:  model.modelData.cancellation
                                color: newOrder
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                        Rectangle{
                            width:50
                            height:50
                            color: "lightblue"


                            Text {
                                font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                                id: contactInfontime
                                text:  1+" min"
                                color: newOrder
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
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
         color: "#7AAEEE"//"#70000000"


        Component {
            id: nameDelegate
            Text {
                text: name+" "+cost
                font.pixelSize: 24
            }
        }




        ListView {

            //currentIndex: 4
            anchors.fill: parent
            clip: true
            model: myModel
            //delegate: nameDelegate
            header: bannercomponent
            footer: Rectangle {
                width: parent.width; height: 50;
                gradient: clubcolors
            }



            focus: true
            delegate:Component {

                Item {
                    //id: item
                    signal qmlSignal(int msg)
                    signal resetSignal()

                    id: container
                    width: ListView.view.width; height: 60; anchors.leftMargin: 10; anchors.rightMargin: 10
                    Rectangle{
                        id:currentTable
                        color: currentIndexT//
                        width: parent.width
                        height: parent.height
                    Rectangle {
                        id: content
                        anchors.centerIn: parent; width: container.width - 40; height: container.height - 10

                        antialiasing: true
                        radius: 10
                        border.color: "black"
                        border.width: 1

                        color: model.modelData.color

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
                    }



                    MouseArea {

                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true

                        onClicked: {
                            container.ListView.view.currentIndex = index
                            container.forceActiveFocus()
                            currentTable.color= "Transparent"
                            con.tableSlot(index + 1)
                        }

                    }
                    states: State {
                                name: "resized"; when: mouseArea.pressed
                                PropertyChanges { target: currentTable; color: "#8EE2FE"}//; height: container.height }
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
                border {
                    color: "#7AAEEE"//"#9EDDF2";
                    width: 2}
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
            GradientStop { position: 0.0; color:"Yellow" }//"#8EE2FE"}
            GradientStop { position: 0.66; color: "#7AAEEE"}
        }
    }

}
