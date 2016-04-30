import QtQuick 2.0

Rectangle {
    visible: if( OrderQueue.queueOrder>0){true} else{false}
    width:parent.width/3
    height: parent.height/10
    anchors.horizontalCenter: parent.horizontalCenter
    gradient: clubcolorsrevers
    Gradient {
        id: clubcolorsrevers
        GradientStop { position: 0.0; color:"#000000"}
        GradientStop { position: 0.90; color: "#8EE2FE"}
    }
    Text{
        text: OrderQueue.queueOrder
        font.family: "FreeSans"
        color: "#000000"
        font.bold: true
        font.pixelSize: parent.height * 0.8
        anchors.verticalCenter: parent.verticalCenter
        anchors.centerIn: parent
        anchors.leftMargin: parent.width * 0.1
        font.capitalization: Font.AllUppercase
    }
}
