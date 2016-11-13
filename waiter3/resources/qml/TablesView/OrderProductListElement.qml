import QtQuick 2.5

Rectangle {
    id: productButton

    property int borderWidth: Math.max(2,parent.width * 0.01)
    property int itemWidth: Math.max(parent.width*0.85,70)

    property bool removeButtonVisible: false
    property double dragThreshold: 0.2

    width: itemWidth
    anchors.right: parent.right
    radius: width/8

    border.width: borderWidth
    border.color: waiterMain.productBorderColor

    clip: true

    Text {
        text: model.modelData.amount + " x " + productList.productName(model.modelData.productId)
        anchors.centerIn: parent
        font.pixelSize: parent.height * 0.4
    }

    Rectangle {
        id: removeOneButton
        opacity: 0

        property int startingPos: -width * 0.9

        width: parent.width - borderWidth * 2
        height: parent.height - borderWidth * 2
        anchors.verticalCenter: parent.verticalCenter

        radius: parent.radius

        x: startingPos

        color: "red"

        state: "Hidden"

        property bool dragActive: dragArea.drag.active
        Drag.dragType: Drag.Automatic
        onDragActiveChanged: {
            if (dragActive) {
                z=2
                removeOneButton.opacity=1
                Drag.start();
            } else {
                z=0

                if (x>startingPos+Math.abs(startingPos*dragThreshold)) {
                    expand.start()
                    state="Expanded"
                }
                else {
                    if (dragArea.containsMouse) removeOneButton.opacity=0.5
                    else removeOneButton.opacity=0
                }
                Drag.drop();
            }
        }

        Text {
            id: removeOneText

            anchors.centerIn: parent

            text: qsTr("Remove one") + langObject.emptyString
            font.pixelSize: parent.height * 0.6
        }

        MouseArea {
            id: dragArea

            anchors.fill: parent
            hoverEnabled: true

            drag.target: parent
            drag.axis: Drag.XAxis
            drag.minimumX: -width * 0.9
            drag.maximumX: productButton.borderWidth

            onEntered: if (!removeOneButton.dragActive && removeOneButton.state==="Hidden") removeOneButton.opacity=0.5
            onExited: if (!removeOneButton.dragActive && removeOneButton.state==="Hidden") removeOneButton.opacity=0

            onClicked: if (removeOneButton.state==="Expanded")
                       {
                           console.log("clicked!")
                           parent.parent.model.amount--
                           console.log("new amount: "+parent.parent.model.amount)
                       }
        }

        NumberAnimation {
            id: expand
            target: removeOneButton
            property: "x"
            duration: 500
            easing.type: Easing.InOutQuad
            to: productButton.borderWidth
        }
    }
}
