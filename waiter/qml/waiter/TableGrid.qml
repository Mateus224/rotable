import QtQuick 2.0

Rectangle {
    id:tableGrid
    width: 520
    height: 400
    x:250
    y:100
    color: "white"


    ListModel {
        id:table
        ListElement {
            pieces: 3
            name: "Samubca"
            price:3
            ready:"true"
            cancellation: "true"
            time:5
            //portrait: "pics/portrait.png"
        }
        ListElement {
            pieces: 3
            name: "Vodka 2cl"
            price:2.5
            ready:"true"
            cancellation: "false"
            time:5
           // portrait: "pics/portrait.png"
        }
        ListElement {
            pieces: 3
            name: "Jägermeister"
            price:3
            ready:"true"
            cancellation: "false"
            time:5
            //portrait: "pics/portrait.png"
        }
        ListElement {
            pieces: 3
            name: "Strawberry lime"
            price:6
            ready:"true"
            cancellation: "false"
            time:5
            //portrait: "pics/portrait.png"
        }
        ListElement {
            pieces: 3
            name: "Vodka RedBull"
            price:8
            ready:"true"
            cancellation: "false"
            time:5
            //portrait: "pics/portrait.png"
        }
        ListElement {
            pieces: 3
            name: "Ficken"
            price:3
            ready:"true"
            cancellation: "false"
            time:5
            //portrait: "pics/portrait.png"
        }

    }


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
        //x:250
        //y:30
        id:grid
        orientation: ListView.Vertical
        width: parent.width
        height: parent.height
        anchors.fill: parent
        Component {
            id: contactsDelegate
            Rectangle {
                //color:"blue"
                //x:200
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
                        //anchors.horizontalCenter: tableGrid.horizontalCenter
                        //anchors.verticalCenter: tableGrid.verticalCenter
                        width:50
                        height:50
                        color: "transparent"


                        Text {
                            //anchors.centerIn: tableGrid
                            font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                            id: contactInfo
                            text:  pieces+"x"
                            color: wrapper.ListView.isCurrentItem ? "red" : "green"

                        }
                    }

                    Rectangle{
                        //anchors.horizontalCenter: tableGrid.horizontalCenter
                        //anchors.verticalCenter: tableGrid.verticalCenter
                        width:150
                        height:50
                        color: "transparent"


                        Text {
                            //anchors.centerIn: tableGrid
                            font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                            id: contactInfoname
                            text:  name
                            color: wrapper.ListView.isCurrentItem ? "red" : "green"

                        }
                    }
                    Rectangle{
                        //anchors.horizontalCenter: tableGrid.horizontalCenter
                        //anchors.verticalCenter: tableGrid.verticalCenter
                        width:50
                        height:50
                        color: "transparent"


                        Text {
                            //anchors.centerIn: tableGrid
                            font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                            id: contactInfoprice
                            text:  price+"€"
                            color: wrapper.ListView.isCurrentItem ? "red" : "green"

                        }
                    }
                    Rectangle{
                        //anchors.horizontalCenter: tableGrid.horizontalCenter
                        //anchors.verticalCenter: tableGrid.verticalCenter
                        width:50
                        height:50
                        color: "transparent"


                        Text {
                            font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                            //anchors.centerIn: tableGrid
                            id: contactInfoready
                            text:  ready
                            color: wrapper.ListView.isCurrentItem ? "red" : "green"

                        }
                    }
                    Rectangle{
                        //anchors.horizontalCenter: tableGrid.horizontalCenter
                        //anchors.verticalCenter: tableGrid.verticalCenter
                        width:50
                        height:50
                        color: "transparent"


                        Text {
                            font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                            id: contactInfoncancellation
                            text:  cancellation
                            color: wrapper.ListView.isCurrentItem ? "red" : "green"

                        }
                    }
                    Rectangle{
                        //anchors.horizontalCenter: tableGrid.horizontalCenter
                        //anchors.verticalCenter: tableGrid.verticalCenter
                        width:50
                        height:50
                        color: "transparent"


                        Text {
                            font.family: "Helvetica"; font.pointSize: 13; font.bold: true
                            id: contactInfontime
                            text:  time+" min"
                            color: wrapper.ListView.isCurrentItem ? "red" : "green"

                        }
                    }
                }
            }
        }

        model: table
        delegate: contactsDelegate
        focus: true
    }


}

