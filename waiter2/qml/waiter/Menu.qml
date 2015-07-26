import QtQuick 2.0

Item {

    width: parent.width
    height:100

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        spacing: 5

        Rectangle{

            Text{
                anchors.centerIn: parent
                text: "Log out"
            }
            color: "red";
            radius: 10.0
            width: parent.width - 10; height: 50
        }

        Rectangle{

            Text{
                anchors.centerIn: parent
                text: "Exit"
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    Qt.quit()
                }
            }

            color: "red";
            radius: 10.0
            width: parent.width - 10; height: 50
        }
    }
}

