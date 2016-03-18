import QtQuick 2.0

// http://qt-project.org/doc/qt-5/qtquick-statesanimations-animations.html
// http://qt-project.org/doc/qt-5/qtquick-modelviewsdata-modelview.html

Rectangle {
    id: productButton
    property int count:0
    property int i:0
    property int stateChangeDuration: 400
    property string buttonFontFamily: "FreeSans"

    property int buttonProductId: -1
    property string productName: ""
    property string productAmount: ""
    property string productInfo: ""
    property string productPriceStr: ""
    property string price:productButton.productPriceStr.replace(",",".")


    property real contentMarginH: grid.buttonWidth * 0.25
    property real contentMarginV: contentMarginH //grid.buttonHeight * 0.075

    property int titleVAlignment: Text.AlignVCenter
    property int titleTopMargin: grid.buttonHeight * 0.01

    state: "COLLAPSED"

    width: grid.buttonWidth
    height: grid.buttonHeight

    Rectangle {
        id: buttonCollapsed
        color: "#00000000"
        anchors.fill: parent

        z: 0

        Text {
            id: idProductNameCollapsed
            anchors.fill: parent
            text: productName ? productName:""

            wrapMode: Text.Wrap

            color: "#FFFFFF"

            verticalAlignment: titleVAlignment
            horizontalAlignment: Text.AlignHCenter

            font.bold: true
            font.pixelSize: grid.buttonHeight * 0.175
            font.family: buttonFontFamily
            font.capitalization: Font.AllUppercase
        }
    }

    Rectangle {
        id: buttonExpanded

        color: parent.color
        visible: false

        x: parent.x
        y: parent.y
        width: parent.width
        height: parent.height


        Text {
            id: idProductNameExpanded
            text: name

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: contentMarginH
            anchors.topMargin: contentMarginV

            height: parent.height * 0.5
            width:  parent.width  * 0.6

            wrapMode: Text.Wrap

            color: "#FFFFFF"

            verticalAlignment: Text.AlignTop
            horizontalAlignment: Text.AlignLeft

            font.bold: true
            font.pixelSize: parent.height * 0.15
            //font.family: productButton.buttonFontFamily
            font.capitalization: Font.AllUppercase
        }

        Text {
            id: idProductPriceStr
            property string price:productButton.productPriceStr.replace(",",".")
            text: parseFloat(price).toFixed(1)+"€ "

            font.bold: true
            anchors.left: productName.right
            anchors.right: parent.right
            anchors.top: parent.top
            //anchors.bottom: productName.bottom
            anchors.rightMargin: contentMarginH
            anchors.topMargin: contentMarginV

            color: "#000000"

            wrapMode: Text.Wrap

            verticalAlignment: Text.AlignTop
            horizontalAlignment: Text.AlignLeft

            font.family: productButton.buttonFontFamily
            font.pixelSize: idProductNameExpanded.font.pixelSize
        }

        Text {
            id: idProductInfo
            text:  info ? info:""

            wrapMode: Text.Wrap

            color: "#000000"

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: contentMarginH
            anchors.rightMargin: contentMarginH

            anchors.top: idProductNameExpanded.bottom
            //anchors.topMargin: parent.height * 0.1

            horizontalAlignment: Text.AlignHCenter

            font.family: productButton.buttonFontFamily
            font.pixelSize: parent.height * 0.075
        }

        //+++++++++++++++++++++++++++++++++++++++
        Rectangle {
            id: idAddProductButton

            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.leftMargin: contentMarginH
            anchors.bottomMargin: contentMarginV

            width: parent.height * 0.2
            height: parent.height * 0.2

            color: Qt.darker(parent.color, 1.4)
            MouseArea {
                anchors.fill: parent

                onClicked: {
                    MyOrder.addToProductHash(buttonProductId)
                    count=count+1
                }

                //onClicked: add_or_removeProduct(buttonProductId,true)

            }

            Image {
                anchors.centerIn: parent
                width: parent.width*0.75
                height: parent.height*0.75
                source: "qrc:/client/resources/plus_white.png"
                anchors.margins: parent.height * 0.33
            }
        }

        Rectangle {
            id: idOrderAmount

            anchors.left: idAddProductButton.right
            anchors.bottom: idAddProductButton.bottom
            anchors.top: idAddProductButton.top

            width: parent.height * 0.2

            color: "#FFFFFF"

            Text {
                id: idProductAmountText
                text: MyOrder.quantity
                color: "#000000"

                anchors.fill: parent

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter

                font.family: productButton.buttonFontFamily
                font.pixelSize: parent.height * 0.75
            }
        }

        //------------------------------------
        Rectangle {
            id: idReduceProductButton

            anchors.left: idOrderAmount.right
            anchors.bottom: idOrderAmount.bottom
            anchors.top: idOrderAmount.top

            width: idAddProductButton.width

            color: idAddProductButton.color
            MouseArea {
                anchors.fill: parent

                onClicked: {
                    MyOrder.rmFromProductHash(buttonProductId)
                    if (count>0)
                        count--
                }

                //onClicked: add_or_removeProduct(buttonProductId,flase)

            }

            Image {
                anchors.centerIn: parent
                width: parent.width*0.75
                height: parent.height*0.75
                source: "qrc:/client/resources/minus_white.png"
                anchors.margins: parent.height * 0.33
            }
        }

        Text {
            id: idProductTotalText
            property string price:productButton.productPriceStr.replace(",",".")
            text: (parseFloat(price).toFixed(1)*(MyOrder.quantity)).toFixed(1)+"€"

            font.bold: true
            anchors.left: idReduceProductButton.right
            anchors.right: parent.right
            anchors.top: idProductInfo.bottom
            anchors.bottom: parent.bottom
            anchors.rightMargin: contentMarginH
            anchors.bottomMargin: contentMarginV

            color: "#000000"

            wrapMode: Text.Wrap

            verticalAlignment: Text.AlignBottom
            horizontalAlignment: Text.AlignRight

            font.family: productButton.buttonFontFamily
            font.pixelSize: parent.height * 0.2//idProductNameExpanded.font.pixelSize
        }

        Behavior on x {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on y {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on width {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on height {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on z {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
    }

    MouseArea {
        id: idButtonGlobalMouseArea
        anchors.fill: parent
        enabled: true
        onClicked:  {
            if (-1 != buttonProductId) {
                if (productButton.state == "COLLAPSED") {
                    productButton.state = "EXPANDED"
                    MyOrder.setproductid(buttonProductId)

                }
            }
        }
    }

    Connections {
        target: idMouseAreaBProductPage
        onClicked: {
            if (-1 != buttonProductId) {
                if (productButton.state == "EXPANDED") {
                    productButton.state = "COLLAPSED"
                    MyOrder.setproductid(buttonProductId)
                }
            }
        }
    }

    states: [
        State {
            name: "EXPANDED"
            PropertyChanges { target: buttonExpanded; visible: true }
            PropertyChanges { target: buttonExpanded; x: -productButton.x }
            PropertyChanges { target: buttonExpanded; y: -productButton.y }
            PropertyChanges { target: buttonExpanded; width: 5 * (grid.buttonWidth + grid.buttonMarginH) - grid.buttonMarginH }
            PropertyChanges { target: buttonExpanded; height: 3 * (grid.buttonHeight + grid.buttonMarginV) - grid.buttonMarginV }
            PropertyChanges { target: productButton; z: 1 }
            PropertyChanges { target: buttonExpanded; z: 1 }
            //PropertyChanges { target: buttonExpanded; MyOrderButton }
        },
        State {
            name: "COLLAPSED"
            PropertyChanges { target: buttonExpanded; visible: false }
            PropertyChanges { target: buttonExpanded; width: grid.buttonWidth }
            PropertyChanges { target: buttonExpanded; height: grid.buttonHeight }
            PropertyChanges { target: buttonExpanded; x: productButton.x }
            PropertyChanges { target: buttonExpanded; y: productButton.y }
            PropertyChanges { target: buttonExpanded; z: 0 }
            PropertyChanges { target: productButton; z: 0 }
        }
    ]
}
