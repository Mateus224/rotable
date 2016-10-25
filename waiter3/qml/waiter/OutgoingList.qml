import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

ListView {

    id: outgoingList

    width: parent.width * 0.33

    spacing: Math.max(10,dataView.height*0.025)

    model: orderFilterToPay

    clip: true

    delegate: OrderListElement { orderTag: "ToPay" }

    DropArea {
        id:outDrop
        anchors.fill: parent

        onEntered:
        {
            if (drag.source.orderTag == "New")
            {
                console.log("drag entered topay list!");
                drag.source.caught = true;
            }
            else console.log("wrong type drag entered topay list!");
        }
        onExited:
        {
            if (drag.source.orderTag == "New")
            {
                console.log("drag left topay list!");
                drag.source.caught = false;
            }
            else console.log("wrong type drag left topay list!");
        }
    }
}
