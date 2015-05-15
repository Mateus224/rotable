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

        Rectangle{
            id: tableWindow
            width: parent.width; height: parent.height
            color: "transparent"//"#70000000"

           /* Component {
                id: nameDelegate
                Text {
                    text: name+" "+cost
                    font.pixelSize: 24
                }
            }*/

            Component {
                id: contactDelegate
                Item {
                    width: grid.cellWidth; height: grid.cellHeight
                    Column {
                        anchors.fill: parent
                        //Image { source: portrait; anchors.horizontalCenter: parent.horizontalCenter }
                        Text { text: name; anchors.horizontalCenter: parent.horizontalCenter }
                    }
                }
            }

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


                Component {     //instantiated when header is processed
                    id: bannercomponentInfo

                    Rectangle {

                        id: banner
                        width: parent.width;
                        height: 60
                        //gradient: clubcolors

                        border {
                            color: "#7AAEEE"//"#9EDDF2";
                            width: 2}
                        Row{

                            spacing: 20
                            x:10
                            Rectangle{


                                width:65
                                height:60
                                color:"transparent"
                                Text {
                                    font.family: "Lobster two"
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    text: "Pieces"
                                    font.pixelSize: 10
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
                                    font.pixelSize: 10
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
                                    font.pixelSize: 10
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
                        y:10
                        id: wrapper
                        width: grid.width
                        height: 60
                        color: "transparent"
                        Rectangle {
                            width: (parent.width)
                            height: (parent.height-2)
                            color: "#7AAEEE"
                        }

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
                                        //text:  pieces+"x"
                                        //color: color_oderinfo
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
                                        text:  name
                                        //color: color_oderinfo
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
                                        text:  priceStr
                                        //color: color_oderinfo
                                        anchors.verticalCenter: parent.verticalCenter
                                        anchors.horizontalCenter: parent.horizontalCenter
                                    }
                                }
                                Rectangle{
                                    width:50
                                    height:50
                                    color: "transparent"

                                    Image {
                                        id: image_ready
                                        anchors.fill: parent
                                        /*source: if(model.modelData.color_oderinfo=== "green")
                                                {
                                                    image_ready.source= "resources/Check.png"
                                                }
                                                else if(model.modelData.color_oderinfo=== "black")
                                                {
                                                    image_ready.source= "resources/Check_grey.png"
                                                }
                                                else if(model.modelData.color_oderinfo=== "red")
                                                {
                                                    image_ready.source= "resources/Check_grey.png"
                                                }
                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked:{
                                                if(model.modelData.color_oderinfo=== "green")
                                                {
                                                    image_ready.source= "resources/Check_grey.png"
                                                }
                                                else if(model.modelData.color_oderinfo=== "black")
                                                {
                                                    image_ready.source= "resources/Check.png"
                                                    image_canc.source= "resources/Cross_grey.png"
                                                }
                                                else if(model.modelData.color_oderinfo=== "red")
                                                {
                                                    image_ready.source= "resources/Check_grey.png"
                                                }
                                                con.readySlot(color_oderinfo, index)
                                            }
                                        }*/
                                    }
                                }
                                Rectangle{
                                    width:50
                                    height:50
                                    color: "transparent"

                                    Image {
                                    id: image_canc
                                    anchors.fill: parent
                                    /*source: if(model.modelData.color_oderinfo=== "red")
                                            {
                                                image_canc.source= "resources/Cross.png"
                                            }
                                            else if(model.modelData.color_oderinfo=== "black")
                                            {
                                                image_canc.source= "resources/Cross_grey.png"
                                            }
                                            else if(model.modelData.color_oderinfo=== "green")
                                            {
                                                image_canc.source= "resources/Cross_grey.png"
                                            }

                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked:{
                                                if(model.modelData.color_oderinfo=== "red")
                                                {
                                                    image_canc.source= "resources/Cross_grey.png"
                                                }
                                                else if(model.modelData.color_oderinfo=== "black")
                                                {
                                                    image_canc.source= "resources/Cross.png"
                                                    image_ready.source= "resources/Check_grey.png"
                                                }
                                                else if(model.modelData.color_oderinfo=== "green")
                                                {
                                                    image_canc.source= "resources/Cross.png"
                                                    image_ready.source= "resources/Check_grey.png"
                                                    color_oderinfo="black"
                                                }
                                                con.cancSlot(color_oderinfo, index)
                                            }
                                        }*/
                                    }
                                }
                            }
                        }
                    }
                }
            }
            Component {     //instantiated when header is processed
                id: bannercomponent
                Rectangle {
                    id: banner
                    width: parent.width; height: 60
                    //gradient: clubcolors
                    border {
                        color: "#7AAEEE"//"#9EDDF2";
                        width: 2}
                    Text {
                        font.family: "Lobster two"
                        anchors.centerIn: parent
                        text: "Tables"
                        font.pixelSize: 32
                        font.bold: true
                    }
                }
            }
        }
    }
}
