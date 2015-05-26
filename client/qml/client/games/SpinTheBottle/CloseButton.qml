import QtQuick 2.0

Rectangle{
    color: "transparent"
    width: 30
    height: 30
    MouseArea{
        anchors.fill: parent
        onClicked: {
            client.state = "STARTSCREEN";
        }
    }

    Image {
        anchors.fill: parent
        //anchors.right: 20
        id: close
        width: 20
        height: 20
        source: "qrc:/client/games/SpinTheBottle/qml/client/games/SpinTheBottle/pics/close.png"
    }
}
