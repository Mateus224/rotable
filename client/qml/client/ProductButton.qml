import QtQuick 2.0

// http://qt-project.org/doc/qt-5/qtquick-statesanimations-animations.html
// http://qt-project.org/doc/qt-5/qtquick-modelviewsdata-modelview.html

Rectangle {
    id: productButton

    property int i:0
    property int stateChangeDuration: 400
    property string buttonFontFamily: "FreeSans"

    property int buttonProductId: -1
    property string productName: ""
    property string productAmount: ""
    property string productInfo: ""
    property string productPriceStr: ""

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
            text: productName

            wrapMode: Text.Wrap

            color: "#FFFFFF"

            verticalAlignment: titleVAlignment
            horizontalAlignment: Text.AlignHCenter

            font.bold: true
            font.pixelSize: grid.buttonHeight * 0.2
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
            text: productName

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: contentMarginH
            anchors.topMargin: contentMarginV

            height: parent.height * 0.3
            width:  parent.width  * 0.7

            wrapMode: Text.Wrap

            color: "#FFFFFF"

            verticalAlignment: Text.AlignTop
            horizontalAlignment: Text.AlignLeft

            font.bold: true
            font.pixelSize: parent.height * 0.2
            font.family: productButton.buttonFontFamily
            font.capitalization: Font.AllUppercase
        }

        Text {
            id: idProductPriceStr
            text: productButton.productPriceStr

            anchors.left: productName.right
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: productName.bottom
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
            text: productInfo

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
                onClicked: { con.payedSlot(1); }
            }

            Image {
                anchors.fill: parent
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
                text: i
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
                onClicked: { con.payedSlot(0); }
            }

            Image {
                anchors.fill: parent
                source: "qrc:/client/resources/minus_white.png"
                anchors.margins: parent.height * 0.33
            }
        }

        Text {
            id: idProductTotalText
            text: "=0,00 €"+buttonProductId

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
            font.pixelSize: idProductNameExpanded.font.pixelSize
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
