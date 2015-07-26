import QtQuick 2.0

Rectangle {

    // Margin left
    anchors.left: tableList.right
    anchors.leftMargin: 10

    //Margin top
    anchors.top: parent.top
    anchors.topMargin: 10

    //Margin bottom
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 10

    //Margin right
    anchors.right: parent.right
    anchors.rightMargin: 10

    height: parent.height

    border.color: "lightsteelblue"
    border.width: 4
    radius: 8
}

