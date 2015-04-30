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
    }

}


