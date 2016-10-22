import QtQuick 2.5

Rectangle {

    id: panelBody

    color: "#0F6E20"

    Image {
        id: moneyImage
        source: "qrc:/resources/images/money.svg"
        fillMode: Image.PreserveAspectFit
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.verticalCenter
    }

    Image {
        id: trashImage
        source: "qrc:/resources/images/trash.svg"
        fillMode: Image.PreserveAspectFit
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.verticalCenter
    }
}
