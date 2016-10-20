import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {

    id: panelBody

    color: "#0F6E20"

    Image {
        id: moneyImage
        source: "qrc:/waiter/images/money.svg"
        fillMode: Image.PreserveAspectFit
<<<<<<< HEAD
        anchors.horizontalCenter: parent.horizontalCenter
=======
>>>>>>> 2ba42cc0a24f99d9aa7fc960c051c99a0f0a6712
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.verticalCenter
    }

    Image {
        id: trashImage
        source: "qrc:/waiter/images/trash.svg"
        fillMode: Image.PreserveAspectFit
<<<<<<< HEAD
        anchors.horizontalCenter: parent.horizontalCenter
=======
>>>>>>> 2ba42cc0a24f99d9aa7fc960c051c99a0f0a6712
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.verticalCenter
    }
}
