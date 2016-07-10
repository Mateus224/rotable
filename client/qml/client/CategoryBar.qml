import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

Rectangle {
    property int buttonSizeH: parent.height * 0.1 * 0.85
    property int buttonSizeW: parent.height * 0.1 * 0.85
    //this tries to calculate optimal number of shown icons based on the bar length (in theory should work on smaller screens)
    property int maxButtonsShown: Math.floor(width / buttonSizeW)
    property var listModel: CategoryListModel

    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.bottomMargin: parent.height * 0.05

    height: parent.height * 0.11

    clip: true

    Image {
        id: backgroundImage
        anchors.fill: parent
        source: "qrc:/client/resources/bg_categories.png"
    }

    ListView {
        width: Math.min(buttonSizeW * model.count, buttonSizeW * maxButtonsShown)
        height: buttonSizeH
        anchors.centerIn: parent
        orientation: ListView.Horizontal

        clip: true
        boundsBehavior: Flickable.DragAndOvershootBounds

        model: listModel

        delegate: Rectangle {

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
                hoverEnabled: true
                onPressed: {
                    parent.color= "#f9a8d8"
                }
                onExited: {
                    parent.color= index % 2 ? "#444041" : "#3f494a"
                }
                onReleased: {
                    parent.color= index % 2 ? "#444041" : "#3f494a"
                    client.currentCategoryId = categoryId
                }
            }
        }
    }
}
