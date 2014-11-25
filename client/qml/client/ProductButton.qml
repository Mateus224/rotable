import QtQuick 2.0

Rectangle {
    // http://qt-project.org/doc/qt-5/qtquick-statesanimations-animations.html
    // http://qt-project.org/doc/qt-5/qtquick-modelviewsdata-modelview.html

    property int stateChangeDuration: 400

    property int buttonProductId: -1
    property string productName: ""
    property string productInfo: ""

    property int lastX: -1
    property int lastY: -1
    property int animating: 0

    property int titleVAlignment: Text.AlignVCenter
    property int titleTopMargin: 5

    width: productButtonSize
    height: productButtonSize

    id: productButton

    state: "COLLAPSED"

    Text {
        id: idProductName
        text: productName
        wrapMode: Text.Wrap
        font.family: "FreeSans"
        color: "#FFFFFF"
        font.pointSize: 15
        anchors.fill: parent
        font.bold: true
        width: parent.width
        verticalAlignment: titleVAlignment
        horizontalAlignment: Text.AlignHCenter
        font.capitalization: Font.AllUppercase
        anchors.topMargin: titleTopMargin

        Behavior on font.pointSize {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
    }

    Text {
        id: idProductInfo
        text: productInfo
        wrapMode: Text.Wrap
        font.family: "FreeSans"
        color: "#FFFFFF"
        font.pointSize: 18
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 20
        anchors.topMargin: 50
        visible: false

        Behavior on visible {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
    }

    Rectangle {
        id: idOrderAmountRect

        border.color: "#FFFFFF"
        border.width: 2

        color: "#00000000"

        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5

        width: 0
        height: 0

        Image {
            id: idMinusButton

            source: "qrc:/images/resources/minus-white-border.png"

            width: parent.width / 5

            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 5
        }

        Text {
            id: idOrderAmount
            text: "0"
            font.family: "FreeSans"
            color: "#FFFFFF"
            font.pointSize: 20
            anchors.left: idMinusButton.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            width: parent.width / 5
            anchors.margins: 5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            visible: false

            Behavior on visible {
                NumberAnimation {
                    duration: stateChangeDuration
                    easing.type: Easing.InOutQuad
                }
            }
        }

        Image {
            id: idPlusButton

            source: "qrc:/images/resources/plus-white-border.png"

            width: parent.width / 5

            anchors.left: idOrderAmount.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 5
        }

        Text {
            id: idOrderTotalCostOfAmount
            text: "0,00 €"
            font.family: "FreeSans"
            color: "#FFFFFF"
            font.pointSize: 20
            anchors.left: idPlusButton.right
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            visible: false

            Behavior on visible {
                NumberAnimation {
                    duration: stateChangeDuration
                    easing.type: Easing.InOutQuad
                }
            }
        }

        Behavior on width {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }

        Behavior on height {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
    }

    MouseArea {
        id: idButtonGlobalMouseArea
        anchors.fill: parent
        enabled: true
        onClicked:  {
            if (-1 != buttonProductId) {
                if (productButton.state == "COLLAPSED") {
                    if (-1 == productButton.lastX) {
                        productButton.lastX = productButton.x
                        productButton.lastY = productButton.y
                    }
                    productButton.state = "EXPANDED"
                }
            }
        }
    }

    Rectangle {
        id: idCloseCrossRect

        anchors.top: parent.top
        anchors.right: parent.right

        width: 0
        height: 0

        color: "#00000000"

        Image {
            id: idCloseCrossImage

            source: "qrc:/images/resources/cross-white-border.png"

            anchors.fill: parent
            anchors.margins: 5
        }

        MouseArea {
            anchors.fill: parent
            onClicked:  {
                productButton.state = "COLLAPSED"
            }
        }

        Behavior on width {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }

        Behavior on height {
            NumberAnimation {
                duration: stateChangeDuration
                easing.type: Easing.InOutQuad
            }
        }
    }

    Behavior on x {
        NumberAnimation {
            duration: stateChangeDuration
            easing.type: Easing.InOutQuad
        }
    }
    Behavior on y {NumberAnimation {
            duration: stateChangeDuration
            easing.type: Easing.InOutQuad
        }
    }
    Behavior on width {
        NumberAnimation {
            duration: stateChangeDuration
            easing.type: Easing.InOutQuad
        }
    }
    Behavior on height {
        NumberAnimation {
            duration: stateChangeDuration
            easing.type: Easing.InOutQuad
        }
    }
    Behavior on z {
        NumberAnimation {
            duration: stateChangeDuration
            easing.type: Easing.InOutQuad
        }
    }
    Behavior on titleVAlignment {
        NumberAnimation {
            duration: stateChangeDuration
            easing.type: Easing.InOutQuad
        }
    }
    Behavior on titleTopMargin {
        NumberAnimation {
            duration: stateChangeDuration
            easing.type: Easing.InOutQuad
        }
    }

    states: [
        State {
            name: "EXPANDED"
            PropertyChanges { target: productButton; width: parent.width - productRects.productButtonMargin }
            PropertyChanges { target: productButton; height: parent.height - productRects.productButtonMargin }
            PropertyChanges { target: productButton; x: parent.x }
            PropertyChanges { target: productButton; y: parent.y }
            PropertyChanges { target: productButton; z: 10 }
            PropertyChanges { target: productButton; titleVAlignment: Text.AlignTop }
            PropertyChanges { target: productButton; titleTopMargin: 20 }
            PropertyChanges { target: idProductInfo; visible: true }
            PropertyChanges { target: idCloseCrossRect; width: 80 }
            PropertyChanges { target: idCloseCrossRect; height: 80 }
            PropertyChanges { target: idProductName; font.pointSize: 20 }
            PropertyChanges { target: idOrderAmountRect; width: 5*85 }
            PropertyChanges { target: idOrderAmountRect; height: 85 }
            PropertyChanges { target: idOrderAmount; visible: true }
            PropertyChanges { target: idOrderTotalCostOfAmount; visible: true }
        },
        State {
            name: "COLLAPSED"
            PropertyChanges { target: productButton; width: productButtonSize }
            PropertyChanges { target: productButton; height: productButtonSize }
            PropertyChanges { target: productButton; x: productButton.lastX }
            PropertyChanges { target: productButton; y: productButton.lastY }
            PropertyChanges { target: productButton; z: 1 }
            PropertyChanges { target: productButton; titleVAlignment: Text.AlignVCenter }
            PropertyChanges { target: productButton; titleTopMargin: 5 }
            PropertyChanges { target: idProductInfo; visible: false }
            PropertyChanges { target: idCloseCrossRect; width: 0 }
            PropertyChanges { target: idCloseCrossRect; height: 0 }
            PropertyChanges { target: idProductName; font.pointSize: 15 }
            PropertyChanges { target: idOrderAmountRect; width: 0 }
            PropertyChanges { target: idOrderAmountRect; height: 0 }
            PropertyChanges { target: idOrderAmount; visible: false }
            PropertyChanges { target: idOrderTotalCostOfAmount; visible: false }
        }
    ]
}
