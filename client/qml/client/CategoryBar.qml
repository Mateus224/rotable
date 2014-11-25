import QtQuick 2.0

Rectangle {
    property int buttonSize: 65
    property var listModel: CategoryListModel

    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 80

    height: buttonSize + 8

    //color: "#FFFFFF"

    Image {
        id: backgroundImage
        anchors.fill: parent
        source: "qrc:/client/resources/bg_orange.png"
    }

    ListView {
        anchors.centerIn: parent
        height: buttonSize
        width: buttonSize * model.count
        orientation: ListView.Horizontal

        model: listModel

        delegate: Rectangle {
            anchors.top: parent.top

            width: buttonSize
            height: buttonSize

            color: index % 2 ? "#444041" : "#5a5758"

            Image {
                anchors.centerIn: parent
                source: "image://rotable/" + icon
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    client.currentCategoryId = categoryId;
                }
            }
        }
    }
}
