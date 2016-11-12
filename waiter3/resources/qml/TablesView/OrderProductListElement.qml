import QtQuick 2.5

Rectangle {
    id: productButton

    property int borderWidth: Math.max(2,parent.width * 0.01)
    property int itemWidth: Math.max(parent.width*0.85,70)

    property bool removeButtonVisible: false

    width: itemWidth
//    anchors.horizontalCenter: parent.horizontalCenter
    anchors.right: parent.right
    radius: width/8

    border.width: borderWidth
    border.color: waiterMain.productBorderColor

    state: "Inactive"

    Text {
        text: model.modelData.amount + " x " + productList.productName(model.modelData.productId)
        anchors.centerIn: parent
        font.pixelSize: parent.height * 0.4
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: {
            removeButtonVisible=!removeButtonVisible
        }
    }

    Rectangle {
        id: removeButton

        visible: removeButtonVisible

        height: parent.height
        width: parent.width * 0.2
        color: "red"
        anchors.centerIn: parent

        property bool dragActive: dragArea.drag.active
        Drag.dragType: Drag.Automatic

        onDragActiveChanged: {
            if (dragActive) {
                Drag.start();
                console.log("red button drag started")
            } else {
                Drag.drop();
                console.log("red button drag ended")
            }
        }

        MouseArea {
            id: dragArea

            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.XAxis
            drag.minimumX: -productButton.width
            drag.maximumX: productButton.width

            onClicked: console.log("clicked tha red button, lol!")
        }
    }
}
