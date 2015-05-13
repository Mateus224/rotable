import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    anchors.topMargin: parent.height * 0.2
    anchors.leftMargin: parent.width * (1.0 - 0.805) / 2.0
    anchors.rightMargin: parent.width * (1.0 - 0.805) / 2.0
    anchors.bottomMargin: parent.height * (0.09125 + 0.10 + 0.125)

    color: "#3f494a"

    Rectangle {
        anchors.fill: parent
        anchors.margins: parent.height * 0.02

        color: "#000000"

        Rectangle{
            id: tableWindow
            width: 200; height: parent.height
            color: "#7AAEEE"//"#70000000"

            Component {
                id: nameDelegate
                Text {
                    text: name+" "+cost
                    font.pixelSize: 24
                }
            }

            ListView {
                anchors.fill: parent
                clip: true
                model: MyProductOrderList
                header: bannercomponent
                footer: Rectangle {
                    width: parent.width; height: 50;

                }
                focus: true

                delegate:Component {
                    Item {
                        id: container
                        width: ListView.view.width; height: 60; anchors.leftMargin: 10; anchors.rightMargin: 10
                        Rectangle{
                            id:currentTable
                            color: currentIndexT//
                            width: parent.width
                            height: parent.height
                            Rectangle {
                                id: content
                                anchors.centerIn: parent; width: container.width - 40; height: container.height - 10

                                antialiasing: true
                                radius: 10
                                border.color: "black"
                                border.width: 1

                                color: model.modelData.color

                                Rectangle { anchors.fill: parent; anchors.margins: 3; color: "#899AAEE0"; antialiasing: true; radius: 8 }
                            }
                            Text {

                                id: label
                                anchors.centerIn: content
                                text: name ? name: ""
                                color: CallWaiter//"White"
                                font.pixelSize: 20
                                font.bold: true
                                font.family: "Lobster two"//font.family: "Purisa"
                            }
                        }

                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            hoverEnabled: true

                            onClicked: {
                                container.ListView.view.currentIndex = index

                            }
                        }
                        states: State {
                                    name: "resized"; when: mouseArea.pressed
                                    PropertyChanges { target: currentTable; color: "#8EE2FE"}//; height: container.height }
                                 }
                    }
                }
            }
            Component {     //instantiated when header is processed
                id: bannercomponent
                Rectangle {
                    id: banner
                    width: parent.width; height: 60
                    //gradient: clubcolors
                    border {
                        color: "#7AAEEE"//"#9EDDF2";
                        width: 2}
                    Text {
                        font.family: "Lobster two"
                        anchors.centerIn: parent
                        text: "Tables"
                        font.pixelSize: 32
                        font.bold: true
                    }
                }
            }
        }
    }
}
