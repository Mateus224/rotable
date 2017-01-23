import QtQuick 2.0

Rectangle {
    anchors.bottom: parent.bottom
    anchors.horizontalCenter:  parent.horizontalCenter
    anchors.bottomMargin: parent.height * 0.175 //0.2
    width: parent.width * 0.35 //0.4
    height: parent.height * 0.07 //0.8
    Gradient {
        id: clubcolorsrevers
        GradientStop { position: 0.0; color:"#000000"}//"#8EE2FE"}
        GradientStop { position: 0.60; color: "#8772c0"}
    }
    Gradient {
        id: clubcolors
        GradientStop { position: 0.0; color:"#f9a8d8"}//"#8EE2FE"}
        GradientStop { position: 0.90; color: "#000000"}
    }
    gradient: clubcolorsrevers
    property string myorderscreen: "MYORDERSCREEN"
    MouseArea {
        id:te
        anchors.fill: parent
        onPressed: {
            parent.gradient=clubcolors
            touchEvent.newTouchEvent()
        }
        onReleased: {
            client.state= myorderscreen
            //ToDo: fix this
            MyOrder.getListForMyOrderPage()
            MyOrder.getListForMyOrderPage()
            MyOrder.setPriceOfOrder()
            onPressed: parent.gradient=clubcolorsrevers
        }
    }
    Text {
        id: buttonLabel
        text: qsTr("MY ORDER")+langObject.emptyString
        font.family: "FreeSans"
        color: "#000000"
        font.bold: true
        font.pixelSize: parent.height * 0.8
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.rightMargin: parent.width * 0.1
    }

}
