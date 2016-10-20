import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

ListView {

    id: orderList

    width: parent.width * 0.33

    spacing: Math.max(10,dataView.height*0.025)

    model: orderFilterNew

    delegate: OrderListElement { orderTag: "New" }

    DropArea {
        anchors.fill: parent

        onEntered:
        {
            console.log("drag entered new list!")
            drag.source.caught = true;
        }
        onExited:
        {
            console.log("drag left new list!")
            drag.source.caught = false;
        }
    }
}
