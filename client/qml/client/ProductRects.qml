import QtQuick 2.0

GridView {
    id: productRects
    property var listModel: ProductListModel

    property int productButtonSize: 125
    property int productButtonMargin: 20

    cellWidth: productButtonSize + productButtonMargin
    cellHeight: productButtonSize + productButtonMargin

    width: 5 * productButtonSize + 5 * productButtonMargin
    height: 3 * productButtonSize + 3 * productButtonMargin

    interactive: false

    Component {
        id: productDelegate

        ProductButton {
            id: productButton
            productName: name
            productInfo: info
            color: rectColor
            buttonProductId: productId
        }
    }

    model: listModel
    delegate: productDelegate
}
