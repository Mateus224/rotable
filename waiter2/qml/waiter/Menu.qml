import QtQuick 2.3
import QtQuick.Layouts 1.1

Column{

    spacing: 10

    Rectangle{

        Text{
            anchors.centerIn: parent
            text: qsTr("Log out")
        }
        color: "gray";
        radius: 10.0
        width: parent.width;
        height: 50
    }

    Rectangle{

        Text{
            anchors.centerIn: parent
            text: qsTr("Exit")
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                Qt.quit()
            }
        }

        color: "red";
        radius: 10.0
        width: parent.width
        height: 50
    }

}
