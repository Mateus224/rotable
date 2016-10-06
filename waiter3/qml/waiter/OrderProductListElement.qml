import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: productButton

    width: parent.width * 0.8
    color: "#6464FE"
    anchors.horizontalCenter: parent.horizontalCenter
    radius: width/10

    Text {
        text: productList.productName(model.modelData.productId)  + " x " + model.modelData.amount
        anchors.centerIn: parent
    }
}
