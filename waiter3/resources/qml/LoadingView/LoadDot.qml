import QtQuick 2.5

Rectangle {
    id: dot

    property int position
    property int totalPoints : symbol.maxPoints
    property int formationRadius : symbol.circleRadius

    property double slice: 2 * Math.PI / totalPoints

    width: parent.width * 0.5
    height: width

    x: formationRadius * Math.cos(slice * position)
    y: formationRadius * Math.sin(slice * position)

    radius: width

    property int counter

    color: if (counter<5) symbol.minGray
            else if (counter==5) symbol.gray1
            else if (counter==6) symbol.gray2
            else symbol.maxGray;

    MouseArea {
        id:area
        anchors.fill: parent
        onClicked: {
            console.log(counter)
            console.log(position)
            console.log(dot.color)
        }
    }
}
