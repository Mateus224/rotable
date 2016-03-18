import QtQuick 2.0

Rectangle {
    property int buttonSizeH: parent.height * 0.1 * 0.85
    property int buttonSizeW: parent.height * 0.1 * 0.85
    property var listModel: CategoryListModel

    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.bottomMargin: parent.height * 0.05

    height: parent.height * 0.11

    Image {
        id: backgroundImage
        anchors.fill: parent
        source: "qrc:/client/resources/bg_categories.png"
    }

    ListView {
        anchors.centerIn: parent
        height: buttonSizeH
        width: buttonSizeW * model.count
        orientation: ListView.Horizontal

        model: listModel

        interactive: false

        delegate: Rectangle {

            anchors.top: parent.top

            width: buttonSizeW
            height: buttonSizeH

            color: index % 2 ? "#444041" : "#3f494a"

            Image {
                anchors.centerIn: parent
                width: buttonSizeH
                height: buttonSizeH
                source: "image://rotable/" + icon
            }

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    parent.color= "#f9a8d8"

                }
                onReleased: {
                    parent.color= index % 2 ? "#444041" : "#3f494a"
                    client.currentCategoryId = categoryId
                }
            }
        }
    }
}
