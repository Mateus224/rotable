import QtQuick 2.0

Rectangle {
    anchors.bottom: parent.bottom
    anchors.horizontalCenter:  parent.horizontalCenter
    anchors.bottomMargin: parent.height * 0.2
    width: parent.width * 0.4
    height: parent.height * 0.08
    Gradient {
        id: clubcolorsrevers
        GradientStop { position: 0.0; color:"#000000"}//"#8EE2FE"}
        GradientStop { position: 0.60; color: "#8772c0"}
    }
    //color: "#3f494a"
    //color: "#f9a8d8"
    gradient: clubcolorsrevers
   /* Image {
        anchors.fill: parent
        source: "qrc:/client/resources/TopBarRight.png"
        antialiasing: true
    }*/
    property string myorderscreen: "MYORDERSCREEN"
    MouseArea {
        id:te
        anchors.fill: parent
        onClicked: {
            client.state= myorderscreen

            //ToDo: fix this
            MyOrder.getListForMyOrderPage()
            MyOrder.getListForMyOrderPage()
            MyOrder.setPriceOfOrder()
        }

    }

    Text {
        id: buttonLabel
        text: "MY ORDER"
        font.family: "FreeSans"
        color: "#000000"
        font.bold: true
        font.pixelSize: parent.height * 0.8
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.rightMargin: parent.width * 0.1
    }

}
