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

        GridView {
            id: grid

            property var listModel: ProductListModel
            property int buttonMarginH: parent.width  * 0.015
            property int buttonMarginV: parent.height * 0.025
            property int buttonWidth:  (parent.width  - buttonMarginH) / 5.01 - buttonMarginH
            property int buttonHeight: (parent.height - buttonMarginV) / 3.01 - buttonMarginV

            anchors.fill: parent
            anchors.leftMargin: buttonMarginH
            anchors.topMargin: buttonMarginV

            cellWidth: buttonWidth + buttonMarginH
            cellHeight: buttonHeight + buttonMarginV

            Component {
                id: productDelegate

                ProductButton {
                    id: productButton
                    productName: name
                    productAmount: amount
                    productInfo: info
                    productPriceStr: priceStr
                    color: rectColor
                    buttonProductId: productId
                }
            }

            model: listModel
            delegate: productDelegate
        }

        Rectangle {
            id: idButtonExpanded

            color: parent.color
            visible: false

            x: parent.x
            y: parent.y
            width: parent.width
            height: parent.height

            z: 1

            Text {
                id: idProductNameExpanded
                text: productName

                anchors.top: parent.top
                anchors.left: parent.left

                height: parent.height * 0.3
                width: parent.width * 0.7

                wrapMode: Text.Wrap

                color: "#FFFFFF"

                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft

                font.bold: true
                font.pixelSize: parent.height * 0.15
                font.family: buttonFontFamily
                font.capitalization: Font.AllUppercase
            }

            Text {
                id: idProductPrice
                text: productPriceStr

                color: "#000000"

                wrapMode: Text.Wrap

                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft

                anchors.left: idProductNameExpanded.right
                anchors.right: parent.right
                anchors.top: idProductNameExpanded.top
                anchors.bottom: idProductNameExpanded.bottom

                font.family: buttonFontFamily
                font.pixelSize: idProductNameCollapsed.font.pixelSize
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
        }
    }
}


