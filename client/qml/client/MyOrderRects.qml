import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    anchors.topMargin: (parent.height * 0.1)*3/2
    anchors.leftMargin: (parent.width * (1.0 - 0.805) / 2.0)*2/3*(1/2*0.82)
    anchors.rightMargin: (parent.width * (1.0 - 0.805) / 2.0)*2/3*(1/2*0.82)
    anchors.bottomMargin: (parent.height * (0.09125 + 0.10 + 0.125))*0.82


    color: "#3f494a"
    property int fontSize: parent.height * 0.02
    property int fontSizeHeader: parent.height * 0.04
    property int widthINFO: parent.width*0.15
    property int heightINFO:parent.height*0.08
    property color defcolor:"#48A8C0" //"#1A1A80" //"#48A8C0"


    Rectangle {
        anchors.fill: parent
        anchors.margins: parent.height * 0.02
        color: "#000000"
        Rectangle{
            id: tableWindow
            width: parent.width; height: parent.height
            color: "transparent"//"#70000000"
            ListView {
                property int buttonMarginH: parent.width  * 0.015
                property int buttonMarginV: parent.height * 0.025

                anchors.fill: parent
                anchors.leftMargin: buttonMarginH
                anchors.rightMargin: buttonMarginH
                anchors.topMargin: buttonMarginV
                anchors.bottomMargin: buttonMarginV
                id:gridL
                orientation: ListView.Vertical
                width: parent.width-0.2
                height: parent.height-0.2
                clip: true
                model: MyProductOrderList
                delegate: contactsDelegate
                header: bannercomponentInfo
                footer: sendOrder
                Component {
                    id: bannercomponentInfo
                    Rectangle {

                        id: banner
                        width: parent.width;
                        height: heightINFO
                        gradient: clubcolors
                        Row{
                            spacing: 20
                            Rectangle{
                                width:widthINFO
                                height:heightINFO
                                color:"transparent"
                                Text {
                                    font.family: "FreeSans"
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.horizontalCenterOffset: 10
                                    text: qsTr("Amount")+langObject.emptyString
                                    font.pixelSize: fontSizeHeader
                                    font.bold: true
                                }
                            }
                            Rectangle{

                                width:widthINFO*1.2
                                height:heightINFO
                                color: "transparent"
                                Text {
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: qsTr("Order")+langObject.emptyString
                                    font.pixelSize: fontSizeHeader
                                    font.bold: true
                                    font.family: "FreeSans"
                                }
                            }
                            Rectangle{

                                width:widthINFO
                                height:heightINFO
                                color:"transparent"
                                    Text {
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: qsTr("Price")+langObject.emptyString
                                    font.pixelSize: fontSizeHeader
                                    font.family: "FreeSans"
                                    font.bold: true
                                }
                            }
                        }
                    }
                }
                Component {
                    id: contactsDelegate
                    Rectangle {
                        y:10
                        id: wrapper
                        width: gridL.width
                        height: heightINFO
                        color: "transparent"
                        Rectangle {
                            width: (parent.width)
                            height: (parent.height-2)
                            color: defcolor// "#7AAEEE"
                        }

                        Rectangle{
                            width:parent.width
                            height: heightINFO
                            color: "transparent"
                            Row {
                                spacing: 20
                                Rectangle{
                                    width:widthINFO
                                    height:heightINFO
                                    color: "transparent"
                                    Text {
                                        font.family: "FreeSans"; font.pointSize: fontSize; font.bold: true
                                        id: contactInfo
                                        text:  amount//+"x"
                                        //color: color_oderinfo
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        anchors.horizontalCenterOffset: 10
                                    }
                                }
                                Rectangle{
                                    width:widthINFO*1.2
                                    height:heightINFO
                                    color: "transparent"
                                    Text {
                                        font.family: "FreeSans"; font.pointSize: fontSize; font.bold: true
                                        id: contactInfoname
                                        text:  name
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }
                                }
                                Rectangle{
                                    width:widthINFO
                                    height:heightINFO
                                    color: "transparent"
                                    Text {
                                        property string price:priceStr.replace(",",".")
                                        text: (parseFloat(price).toFixed(1)*amount).toFixed(1) +" € "
                                        font.family: "FreeSans"; font.pointSize: fontSize; font.bold: true
                                        id: contactInfoprice
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }
                                }
                                Rectangle{
                                    width:heightINFO*0.8
                                    height:heightINFO*0.8
                                    color: "transparent"
                                    Image {
                                        id: image_ready
                                        anchors.fill: parent
                                        source: image_ready.source= "resources/plus_white.png"
                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked:{
                                                touchEvent.newTouchEvent()
                                                MyOrder.addToProductHash(productId)
                                                MyOrder.addProductFromGuiTo_orderProducts(productId)
                                            }
                                        }
                                    }
                                }
                                Rectangle{
                                    width:heightINFO*0.8
                                    height:heightINFO*0.8
                                    color: "transparent"

                                    Image {
                                    id: image_canc
                                    anchors.fill: parent
                                    source: image_canc.source = "resources/minus_white.png"

                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked:{
                                                touchEvent.newTouchEvent()
                                                MyOrder.rmFromProductHash(productId)
                                                MyOrder.removeProductFromGuiTo_orderProducts(productId)
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                Component{
                    id:sendOrder
                    Rectangle {
                        id: endPrice
                        width: parent.width;
                        height: heightINFO
                        gradient: clubcolorsrevers
                        Rectangle {
                            anchors.verticalCenter:parent.verticalCenter
                            x:parent.width/4
                            width: parent.width/4
                            id: sendOrderButton
                            height: parent.height*0.66
                            border.color: "#8772c0"
                            border.width: 2
                            color: defcolor
                            Timer {
                                id:sendOrderTimer
                                interval:1500
                                onTriggered: {
                                  client.state="STARTSCREEN"
                                    sendOrderTimer.stop();
                                }
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    touchEvent.newTouchEvent()
                                    if(MyOrder.b_acceptOrder())
                                    {
                                        client.sendOrder()
                                        client.state = "SENTPAGE"
                                        MyOrder.clearList()
                                        //sendOrderTimer.start()
                                    }
                                    else
                                    {
                                        client.state = "SENTPAGE"
                                        //sendOrderTimer.start()
                                    }
                                }
                                onPressed: parent.color= "#8772c0"
                                onReleased: {
                                    parent.color=defcolor
                                }
                                Text {
                                    font.family: "FreeSans"; font.pointSize: fontSize; font.bold: true
                                    text:  qsTr("Send Order")+langObject.emptyString
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }
                            }
                        }
                        Rectangle {
                            id: endPriceDoub
                            x:parent.width/2
                            width: parent.width/2;
                            height: heightINFO
                            gradient: clubcolorsrevers
                            Text {
                                font.family: "FreeSans"; font.pointSize: fontSize; font.bold: true
                                text:  MyOrder.PriceOfOrder+" € "
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                    }
                }
            }
        }
    }
    Gradient {
        id: clubcolors
        GradientStop { position: 0.0; color:"#f9a8d8" }//"#8EE2FE"}
        GradientStop { position: 0.80; color: defcolor}
    }
    Gradient {
        id: clubcolorsrevers
        GradientStop { position: 0.0; color:defcolor}//"#8EE2FE"}
        GradientStop { position: 0.60; color: "#8772c0"}
    }
}
