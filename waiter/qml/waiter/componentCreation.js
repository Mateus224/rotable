var component;
var sprite;
var count_table_objects=0


var count=100
function createSpriteObjects(){
    var string=["import QtQuick 2.0;

    Rectangle {
    x:"+100+";
    y: "+count+";
    width: 100;
    height: 50;
    color:\"#800000FF\";

    Text {
        text:\"table:\"+ "+count_table_objects+"
    }
    MouseArea {
    id: itemArea"+count_table_objects+";
    anchors.fill: parent;
    }
}




"]



    Qt.createQmlObject(string, appWindow, "dynamicItem");
    count=count+100
    count_table_objects++
}
