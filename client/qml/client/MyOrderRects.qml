import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    anchors.topMargin: parent.height * 0.2
    anchors.leftMargin: parent.width * (1.0 - 0.805) / 2.0
    anchors.rightMargin: parent.width * (1.0 - 0.805) / 2.0
    anchors.bottomMargin: parent.height * (0.09125 + 0.10 + 0.125)
    property int fontSize: parent.height * 0.02
    property int fontSizeHeader: parent.height * 0.04
    property int widthINFO: parent.width*0.15
    property int heightINFO:parent.height*0.08
    property color defcolor:"#48A8C0" //"#1A1A80" //"#48A8C0"

    color: "#3f494a"

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
                id:grid
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

                        border {
                            color: "white"//"#7AAEEE"//"#9EDDF2";
                            width: 2}
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
                                    text: "Amount"
                                    font.pixelSize: fontSizeHeader
                                    font.bold: true

                                }
                            }
                            Rectangle{

                                width:widthINFO
                                height:heightINFO
                                color: "transparent"
                                Text {
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: "Order"
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
                                    text: "Price"
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
                        width: grid.width
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

                                    }
                                }

                                Rectangle{
                                    width:widthINFO
                                    height:heightINFO
                                    color: "transparent" //"transparent"

                                    Text {
                                        font.family: "FreeSans"; font.pointSize: fontSize; font.bold: true
                                        id: contactInfoname
                                        text:  name
                                        //color: color_oderinfo
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
                                        //text:  priceStr
                                        //color: clubcolors
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

                        id: banner
                        width: parent.width;
                        height: heightINFO
                        gradient: clubcolors
                        Text {
                            font.family: "FreeSans"; font.pointSize: fontSize; font.bold: true
                            id: contactInfoname
                            text:  "Price"
                            //color: color_oderinfo
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }
            }
        }
    }
    Gradient {
        id: clubcolors
        GradientStop { position: 0.0; color:"White" }//"#8EE2FE"}
        GradientStop { position: 0.66; color: defcolor}
    }
}
