import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

ListView {

    id: outgoingList

    width: parent.width * 0.33

    spacing: Math.max(10,dataView.height*0.025)

    model: orderFilterToPay

    delegate: OrderListElement {}

    DropArea {
        anchors.fill: parent

        onEntered:
        {
            console.log("drag entered!")
            drag.source.caught = true;
        }
        onExited:
        {
            console.log("drag left!")
            drag.source.caught = false;
        }
    }
}
