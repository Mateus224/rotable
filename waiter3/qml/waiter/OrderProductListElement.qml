import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: productButton

    property int borderWidth: Math.max(2,parent.width * 0.01)
<<<<<<< HEAD
    property int itemWidth: Math.max(parent.width*0.8,80)
=======
    property int itemWidth: Math.max(parent.width*0.7,70)
>>>>>>> 2ba42cc0a24f99d9aa7fc960c051c99a0f0a6712

    width: itemWidth
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
