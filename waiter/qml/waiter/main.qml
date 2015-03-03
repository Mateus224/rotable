import QtQuick 2.0
import QtMultimedia 5.0
import "componentCreation.js" as JSinterface



Rectangle {
    id: appWindow
    width: 1024; height: 768
    color:"lightblue"//"#800000FF"



    Rectangle{
        id:downWindow
        x:950
        height: parent.height
        width:  parent.width
        color: "#7AAEEE"
    }

    Rectangle{
        id:ob
        x:220
        width: 710
        height: 150
        y: parent.height-150
        color: "#7AAEEE"

        Text {
            id:priceLabel
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.bold: true
            font.family: "Lobster two"
            font.pixelSize: 32
            text:JSinterface.getPrices()
            y:60

        }

        Rectangle
        {
            y:0
            width:parent.width
            height:60
            gradient: clubcolors
        }
        Rectangle
        {

            width:parent.width
            height:60
            y:  ob.height-40
            //color:"black"

            gradient: clubcolors2
        }
    }


    Rectangle {
        id:tableGrid
        width: 710
        height: parent.height-150
        x:220
        y:0
        color: "lightblue"//"#7AAEEE"
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
                    width: parent.width;
                    height: 60
                    gradient: clubcolors

                    border {
                        color: "#7AAEEE"//"#9EDDF2";
                        width: 2}
                    Row{

                        spacing: 20
                        x:10
                        Rectangle{


                            width:65
                            height:60
                            color:"transparent"
                            Text {
                                font.family: "Lobster two"
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "Pices"
                                font.pixelSize: 32
                                font.bold: true

                            }
                        }
                        Rectangle{

                            width:280
                            height:60
                            color: "transparent"
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "Order"
                                font.pixelSize: 32
                                font.bold: true
                                font.family: "Lobster two"
                            }
                        }
                        Rectangle{

                            width:80
                            height:60
                            color:"transparent"
                                Text {
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "Price"
                                font.pixelSize: 32
                                font.family: "Lobster two"
                                font.bold: true
                            }
                        }
                    }

                }
            }

            Component {
                id: contactsDelegate
                Rectangle {

                    x:10
                    id: wrapper
                    width: grid.width
                    height: 60
                    color: "transparent"//"blue"

                    Rectangle{
                        width:parent.width
                        height: 50
                        color: "transparent"

                        Row {
                            spacing: 20

                            Rectangle{
                                width:65
                                height:50
                                color: "transparent"

                                Text {
                                    font.family: "Purisa"; font.pointSize: 16; font.bold: true
                                    id: contactInfo
                                    text:  pieces+"x"
                                    color: newOrder
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter

                                }
                            }

                            Rectangle{
                                width:280
                                height:50
                                color: "transparent" //"transparent"

                                Text {
                                    font.family: "Purisa"; font.pointSize: 16; font.bold: true
                                    id: contactInfoname
                                    text:  orderName
                                    color: newOrder
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }
                            }
                            Rectangle{
                                width:80
                                height:50
                                color: "transparent"



                                Text {
                                    font.family: "Purisa"; font.pointSize: 16; font.bold: true
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
                                color: "transparent"
                            property bool ready:false
                                Image {
                                id: reaady
                                anchors.fill: parent
                                //source: "resources/Cross.png";
                                source: (model.modelData.ready=== reaady) ? "resources/Check_grey.png" : "resources/Check.png"
                                }

                                /*Text {
                                    font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                                    id: contactInfoready
                                    text:  model.modelData.ready
                                    color: newOrder
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }*/
                            }
                            Rectangle{
                                width:50
                                height:50
                                color: "transparent"

                                Image {
                                id: canc
                                anchors.fill: parent
                                source: (model.modelData.ready=== reaady) ? "resources/Cross_grey.png" : "resources/Cross_grey.png"

                                }

                                /*Text {
                                    font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                                    id: contactInfoncancellation
                                    text:  model.modelData.cancellation
                                    color: newOrder
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }*/
                            }
                            Rectangle{
                                width:60
                                height:50
                                color: "transparent"


                                Text {
                                    font.family: "Purisa"; font.pointSize: 16; font.bold: true
                                    id: contactInfontime
                                    text:  1+"min"
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
                    property real toPay:ToPay
                    signal qmlSignal(int msg)


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
                        font.pixelSize: 20
                        font.bold: true
                        font.family: "Lobster two"//font.family: "Purisa"
                    }
                    }



                    MouseArea {

                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true

                        onClicked: {
                            JSinterface.setPrices(ToPay)
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
                width: parent.width; height: 60
                gradient: clubcolors
                border {
                    color: "#7AAEEE"//"#9EDDF2";
                    width: 2}
                Text {
                    font.family: "Lobster two"
                    anchors.centerIn: parent
                    text: "Tables"
                    font.pixelSize: 32
                    font.bold: true
                }
            }
        }
    }
    Gradient {
        id: clubcolors
        GradientStop { position: 0.0; color:"White" }//"#8EE2FE"}
        GradientStop { position: 0.66; color: "#7AAEEE"}
    }
    Gradient {
        id: clubcolors2
        GradientStop { position: 0.0; color:"#7AAEEE" }//"#8EE2FE"}
        GradientStop { position: 0.66; color: "White"}
    }

}
