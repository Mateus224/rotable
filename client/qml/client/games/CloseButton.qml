import QtQuick 2.0


Rectangle{
    color: "transparent"
    width: parent.width
    height: parent.height

    Image {
        id: close0
        x:25
        y:25

        width: 30
        height: 30
        source: "qrc:/client/games/SpinTheBottle/qml/client/games/SpinTheBottle/pics/close.png"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                gamePage.state = "DEFAULT"
                client.screenRotation
            }
        }
    }
    Image {
        id: close1
        x: 25
        y:parent.height-50
        width: 30
        height: 30
        source: "qrc:/client/games/SpinTheBottle/qml/client/games/SpinTheBottle/pics/close.png"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                gamePage.state = "DEFAULT"
                client.screenRotation
            }
        }
    }
    Image {
        id: close2
        x:parent.width-50
        y:25
        width: 30
        height: 30
        source: "qrc:/client/games/SpinTheBottle/qml/client/games/SpinTheBottle/pics/close.png"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                gamePage.state = "DEFAULT"
                client.screenRotation
            }
        }
    }
    Image {
        id: close3
        x:parent.width-50
        y:parent.height-50
        width: 30
        height: 30
        source: "qrc:/client/games/SpinTheBottle/qml/client/games/SpinTheBottle/pics/close.png"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                gamePage.state = "DEFAULT"
                client.screenRotation
            }
        }
    }
}
