import QtQuick 2.5
import QtGraphicalEffects 1.0

//warning: this file is unused, instead please modify right panel rect inside TablesView.qml

Rectangle {

    id: panelBody

    DropShadow {
        anchors.fill: moneyImage
        radius: 25
        samples: 51
        spread: 0.5
        color: "#ff00FF00"
        source: moneyImage
    }

    DropShadow {
        anchors.fill: trashImage
        radius: 25
        samples: 51
        spread: 0.4
        color: "#ffFF0000"
        source: trashImage
    }

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
