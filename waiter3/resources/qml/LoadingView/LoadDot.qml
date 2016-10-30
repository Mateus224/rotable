import QtQuick 2.5

Rectangle {
    id: dot

    property int position
//    property int posOffset: waiterMain * 0.5

    width: parent.width* 0.3
    height: width

    x: position <= 4 ? position * width : (8 - position) * width
    y: Math.sin(position * Math.PI/4) * width * 2

    radius: width
    color: "grey"
}
