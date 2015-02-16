import QtQuick 2.0

Rectangle {
    id:tableGrid
    width: 520
    height: 400
    x:250
    y:30


    ListModel {
        id:table
        ListElement {
            pieces: 3
            name: "Jim Williams"
            price:3
            //portrait: "pics/portrait.png"
        }
        ListElement {
            pieces: 3
            name: "John Brown"
            price:3
           // portrait: "pics/portrait.png"
        }
        ListElement {
            pieces: 3
            name: "Bill Smyth"
            number:3
            price:3
            //portrait: "pics/portrait.png"
        }
        ListElement {
            pieces: 3
            name: "Sam Wise"
            price:3

            //portrait: "pics/portrait.png"
        }
        ListElement {
            pieces: 3
            name: "Sama Wise"
            price:3
            //portrait: "pics/portrait.png"
        }
        ListElement {
            pieces: 3
            name: "Samee Wise"
            price:3
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

        orientation: ListView.Vertical
        width: parent.width-20
        height: 500
        //cellWidth: 80; cellHeight: 80

        Component {
            id: contactsDelegate
            Rectangle {
                id: wrapper
                width: 80
                height: 50
                //color: ListView.isCurrentItem ? "white" : "red"
                color: "white"
                Text {
                    anchors.horizontalCenter: wrapper.horizontalCenter
                    anchors.verticalCenter: wrapper.verticalCenter
                    id: contactInfo
                    text:  pieces
                    color: wrapper.ListView.isCurrentItem ? "red" : "green"
                }
            }

        }

        model: table
        delegate: contactsDelegate
        focus: true
    }


}

