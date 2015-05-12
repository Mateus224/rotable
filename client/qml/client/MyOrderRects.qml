import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    anchors.topMargin: parent.height * 0.2
    anchors.leftMargin: parent.width * (1.0 - 0.805) / 2.0
    anchors.rightMargin: parent.width * (1.0 - 0.805) / 2.0
    anchors.bottomMargin: parent.height * (0.09125 + 0.10 + 0.125)

    color: "#3f494a"

    Rectangle {
        anchors.fill: parent
        anchors.margins: parent.height * 0.02

        color: "#000000"

        ListView {
            id: list
            property var listModel: MyProductOrderList
            property int buttonMarginH: parent.width  * 0.015
            property int buttonMarginV: parent.height * 0.025
            property int buttonWidth:  (parent.width  - buttonMarginH) / 5.01 - buttonMarginH
            property int buttonHeight: (parent.height - buttonMarginV) / 3.01 - buttonMarginV

            anchors.fill: parent
            orientation: ListView.Vertical
            anchors.leftMargin: buttonMarginH
            anchors.topMargin: buttonMarginV
            width:parent.width
            height: 20



            clip: true
            //anchors.leftMargin: buttonMarginH
            //anchors.topMargin: buttonMarginV
            Component {     //instantiated when header is processed
                id: bannercomponentInfo

                Rectangle {
                    color: "transparent"
                    id: banner
                    width: parent.width;
                    height: 100
                    //gradient: clubcolors

                    border {
                        color: "lightblue"//"#9EDDF2";
                        width: 2}
                    Row{

                        spacing: 20
                        //x:10
                        Rectangle{


                            width:65
                            height:60
                            color:"transparent"
                            Text {
                                font.family: "Lobster two"
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "Pieces"
                                font.pixelSize: 32
                                font.bold: true

                            }
                        }
                        Rectangle{

                            width:280
                            height:60
                            color: "transparent"
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "Order"
                                font.pixelSize: 32
                                font.bold: true
                                font.family: "Lobster two"
                            }
                        }
                        Rectangle{

                            width:80
                            height:60
                            color:"transparent"
                                Text {
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "Price"
                                font.pixelSize: 32
                                font.family: "Lobster two"
                                font.bold: true
                            }
                        }
                    }
                }
            }

            Component {
                id: contactsDelegate
                Rectangle {
                    x:10
                    id: wrapper
                    width: grid.width
                    height: 60
                    color: "transparent"

                    Rectangle{
                        width:parent.width
                        height: 50
                        color: "transparent"

                        Row {

                            spacing: 20

                            Rectangle{
                                width:65
                                height:50
                                color: "transparent"

                                Text {
                                    font.family: "Purisa"; font.pointSize: 16; font.bold: true
                                    id: contactInfo
                                    text:  pieces+"x"
                                    color: color_oderinfo
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter

                                }
                            }

                            Rectangle{
                                width:280
                                height:50
                                color: "transparent" //"transparent"

                                Text {
                                    font.family: "Purisa"; font.pointSize: 16; font.bold: true
                                    id: contactInfoname
                                    text:  orderName
                                    color: color_oderinfo
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }
                            }
                            Rectangle{
                                width:80
                                height:50
                                color: "transparent"

                                Text {
                                    font.family: "Purisa"; font.pointSize: 16; font.bold: true
                                    id: contactInfoprice
                                    text:  price.toFixed(2)+"€"
                                    color: color_oderinfo
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }
                            }

                            Rectangle{
                                width:50
                                height:50
                                color: "transparent"
                                }
                            }
                            Rectangle{
                                width:60
                                height:50
                                color: "transparent"


                                Text {
                                    font.family: "Purisa"; font.pointSize: 16; font.bold: true
                                    id: contactInfontime
                                    text:  1+"min"
                                    color: color_oderinfo
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }
                            }
                        }
                    }

            }

            /*Component {
                id: productDelegate

                ProductButton{
                    id: productButton
                    productName: name ? name:""
                    productAmount: amount ? amount:""
                    productInfo: info ? info:""
                    productPriceStr: priceStr ? priceStr:""
                    color: rectColor ? rectColor:""
                    buttonProductId: productId ? productId:""
                }
            }*/

        model: listModel
        delegate: contactsDelegate

        }
    }
}
