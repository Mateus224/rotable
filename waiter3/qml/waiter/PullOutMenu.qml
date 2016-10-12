import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: mainMenuLayout

    state: "Expand"

    property int menuItemHeight: Math.max(30,dataView.height * 0.1)
    property int menuWidth: waiterMain.width * 0.3
    property real autoScrollTreshhold: 0.3

    property int scrollTimeMax: 500

    Rectangle {
        id: dragButton

        anchors.verticalCenter: parent.verticalCenter

        width: waiterMain.width * 0.03
        height: width

        border.width: 1
        border.color: "#000000"

        property int collapseDuration: (x/menuWidth)*scrollTimeMax
        property int expandDuration: ((menuWidth-x)/menuWidth)*scrollTimeMax
        property bool expanding: mainMenuLayout.state=="Expand"

        property bool dragActive: dragArea.drag.active
        Drag.dragType: Drag.Automatic
        onDragActiveChanged: {
            if (dragActive) {
                Drag.start();
            } else {
                if (mainMenuLayout.state=="Expand")
                    if (x>=menuWidth*autoScrollTreshhold)
                    {
                        expand.start()
                        mainMenuLayout.state="Collapse"
                    }
                    else collapse.start()
                else
                    if (x>=menuWidth*(1-autoScrollTreshhold)) expand.start()
                    else
                    {
                        collapse.start()
                        mainMenuLayout.state="Expand"
                    }

                Drag.drop();
            }
        }

        Text {
            id: arrowtext
            text: ">"
            font.pixelSize: parent.height
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -2
        }

        MouseArea {
            id: dragArea

            anchors.fill: parent
            drag.target: parent
            drag.axis: Drag.XAxis
            drag.minimumX: 0
            drag.maximumX: menuWidth
        }

        NumberAnimation {
            id: expand
            target: dragButton
            property: "x"
            duration: Math.max(10,dragButton.expandDuration)
            easing.type: Easing.InOutQuad
            to: menuWidth
        }

        NumberAnimation {
            id: collapse
            target: dragButton
            property: "x"
            duration: Math.max(10,dragButton.collapseDuration)
            easing.type: Easing.InOutQuad
            to: 0
        }
    }

    Rectangle {
        id: dragMenu

        width: menuWidth
        height: waiterMain.height - timeBar.height

        anchors.right: dragButton.left
        anchors.top: parent.top

        border.width: 1
        border.color: "#000000"

        PullOutMenuElement {
            id:orderButton
            nameText: qsTr("Orders") + langObject.emptyString
            height: mainMenuLayout.menuItemHeight
            selected: true

            anchors.top: parent.top

            MouseArea {
                id: orderMouseArea
                anchors.fill: parent
                onClicked: {
                    dataView.state="Tables"
                    orderButton.selected=true
                    archiveButton.selected=false
                    configButton.selected=false
                    languageButton.selected=false
                    logoutButton.selected=false
                }
            }
        }

        PullOutMenuElement {
            id:archiveButton
            nameText: qsTr("Archive") + langObject.emptyString
            height: mainMenuLayout.menuItemHeight

            anchors.top: orderButton.bottom

            MouseArea {
                id: archiveMouseArea
                anchors.fill: parent
                onClicked: {
                    dataView.state="NotImplemented"
                    orderButton.selected=false
                    archiveButton.selected=true
                    configButton.selected=false
                    languageButton.selected=false
                    logoutButton.selected=false
                }
            }
        }

        PullOutMenuElement {
            id:configButton
            nameText: qsTr("Configuration") + langObject.emptyString
            height: mainMenuLayout.menuItemHeight

            anchors.top: archiveButton.bottom

            MouseArea {
                id: configMouseArea
                anchors.fill: parent
                onClicked: {
                    dataView.state="NotImplemented"
                    orderButton.selected=false
                    archiveButton.selected=false
                    configButton.selected=true
                    languageButton.selected=false
                    logoutButton.selected=false
                }
            }
        }

        PullOutMenuElement {
            id:languageButton
            nameText: qsTr("Language") + langObject.emptyString
            height: mainMenuLayout.menuItemHeight

            anchors.top: configButton.bottom

            MouseArea {
                id: languageMouseArea
                anchors.fill: parent
                onClicked: {
                    dataView.state="NotImplemented"
                    orderButton.selected=false
                    archiveButton.selected=false
                    configButton.selected=false
                    languageButton.selected=true
                    logoutButton.selected=false
                }
            }
        }

        PullOutMenuElement {
            id:logoutButton
            nameText: qsTr("Logout") + langObject.emptyString
            height: mainMenuLayout.menuItemHeight

            anchors.top: languageButton.bottom

            MouseArea {
                id: logoutMouseare
                anchors.fill: parent
                onClicked: {
                    dataView.state="NotImplemented"
                    orderButton.selected=false
                    archiveButton.selected=false
                    configButton.selected=false
                    languageButton.selected=false
                    logoutButton.selected=true
                    Qt.quit()
                }
            }
        }
    }

    states: [
        State {
            name: "Expand"
            PropertyChanges {
                target: arrowtext
                text: ">"
            }
        },

        State {
            name: "Collapse"
            PropertyChanges {
                target: arrowtext
                text: "<"
            }
        }
    ]
}
