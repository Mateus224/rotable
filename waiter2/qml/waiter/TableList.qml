import QtQuick 2.0

Rectangle {
    // Set minimal size of left sidebar
    width: Math.max(100,parent.width/5)
    height:parent.heigh
    color:"lightblue"
    //anchors.margins: 30

    anchors.left: parent.left
    anchors.leftMargin: 10

    anchors.top: parent.top
    anchors.topMargin: 10

    //In future field with table data
    Rectangle {

        width: parent.width
        height: 50
        color: "white"
        border.color: "lightsteelblue"
        border.width: 4
        radius: 8

    }
}

