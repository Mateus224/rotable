import QtQuick 2.5
import QtGraphicalEffects 1.0

Rectangle {
    id: productButton

    property int borderWidth: Math.max(2,parent.width * 0.02)
    property int itemWidth: Math.max(parent.width,70)

    property double dragThreshold: 0.2

    width: itemWidth
    anchors.horizontalCenter: parent.horizontalCenter
    radius: width/8

    border.width: borderWidth
    border.color: waiterMain.productBorderColor

    clip:true

    //state: "RemoveOne"
    property string dragState: "Product"

    layer.enabled: true
    layer.effect: OpacityMask {
            maskSource: Item {
                width: productButton.width
                height: productButton.height
                Rectangle {
                    anchors.centerIn: parent
                    width: parent.width
                    height: parent.height
                    radius: width/8
                }
            }
        }

    Rectangle {
        id: productName
        width: parent.width
        height: parent.height
        radius: parent.radius

        border.width: borderWidth
        border.color: waiterMain.productBorderColor

        property int maxLeft: -width * 0.87
        property int maxRight: width * 0.87

        z:1

        onXChanged: {
            if (x<0) parent.state="RemoveAll"
            if (x>0) parent.state="RemoveOne"
        }

        property bool dragActive: dragArea.drag.active
        Drag.dragType: Drag.Automatic
        onDragActiveChanged: {
            if (dragActive) {
                Drag.start();
            } else {
                if (parent.dragState==="Product")
                {
                    if (x < dragThreshold*maxLeft) {
                        parent.dragState="RemoveAll"
                        goLeft.start()
                    }
                    else if (x > maxRight*dragThreshold) {
                        parent.dragState="RemoveOne"
                        goRight.start()
                    }
                    else goMiddle.start()
                }
                else if (parent.dragState==="RemoveOne")
                {
                    if (x > (1-dragThreshold)*maxRight) goRight.start()
                    else if (x > 0) {
                        parent.dragState="Product"
                        goMiddle.start()
                    }
                    else {
                        parent.dragState="RemoveAll"
                        goLeft.start()
                    }
                }
                else
                {
                    if (x < (1-dragThreshold)*maxLeft) goLeft.start()
                    if (x < 0) {
                        parent.dragState="Product"
                        goMiddle.start()
                    }
                    else goRight.start()
                }
                Drag.drop();
            }
        }

        MouseArea {
            id:dragArea
            anchors.fill: productName

            drag.target: productName
            drag.axis: Drag.XAxis
            drag.minimumX: productName.maxLeft
            drag.maximumX: productName.maxRight
        }

        Text {
            text: model.modelData.amount + " x " + productList.productName(model.modelData.productId)
            anchors.centerIn: parent
            font.pixelSize: parent.height * 0.4
        }

        PropertyAnimation {
            id: goLeft
            target: productName
            property: "x"
            duration: 500
            to: productName.maxLeft
        }
        PropertyAnimation {
            id: goMiddle
            target: productName
            property: "x"
            duration: 500
            to: 0
        }
        PropertyAnimation {
            id: goRight
            target: productName
            property: "x"
            duration: 500
            to: productName.maxRight
        }
    }

    Rectangle {
        id: removeButton

        width: parent.width
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter

        radius: parent.radius

        color: productButton.state==="RemoveOne"?"#FF0000":"#DD0000"

        Text {
            id: removeOneText

            anchors.centerIn: parent

            property string removeText: productButton.state==="RemoveOne"?qsTr("Remove one"):qsTr("Remove all")

            text: removeText + langObject.emptyString
            font.pixelSize: parent.height * 0.6
        }

        MouseArea {
            id: removeArea

            anchors.fill: parent

            onClicked:
            {
                console.log("Clicked!")
                if (productButton.dragState==="RemoveOne") {
                    productButton.parent.readyOrder
                    modelData.amount--
                    console.log("Removed one!")
                }
                else if (productButton.dragState==="RemoveAll")
                {
                    model.modelData.change = true
                    orderboard.changeState(2);
                }
            }
        }
    }

    Rectangle {
        id: borderOnly

        z:2
        width: parent.width
        height: parent.height
        radius: parent.radius

        color: "transparent"

        border.width: borderWidth
        border.color: waiterMain.productBorderColor
    }
}
