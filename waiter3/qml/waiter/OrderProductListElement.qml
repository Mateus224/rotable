import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: productButton

    property int borderWidth: Math.max(4,parent.width * 0.02)

    width: parent.width * 0.9
    anchors.horizontalCenter: parent.horizontalCenter
    radius: width/8

    border.width: borderWidth
    border.color: "#6464FE"

    Text {
        text: productList.productName(model.modelData.productId)  + " x " + model.modelData.amount
        anchors.centerIn: parent
        font.pixelSize: parent.height * 0.4
    }
}