import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: mainMenuLayout

    state: "Hidden"

    property int menuItemHeight: Math.max(30,dataView.height * 0.1)

    Rectangle {
        id: dragButton

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: dragMenu.right

        width: waiterMain.width * 0.03
        height: width

        border.width: 1
        border.color: "#000000"

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

            onClicked: {
                if (mainMenuLayout.state=="Hidden")
                {
                    mainMenuLayout.state="Open"
                    arrowtext.text="<"
                }
                else
                {
                    mainMenuLayout.state="Hidden"
                    arrowtext.text=">"
                }
            }
        }
    }

    Rectangle {
        id: dragMenu

        width: waiterMain.width * 0.3
        height: waiterMain.height - timeBar.height

        anchors.right: parent.left
        anchors.top: parent.top

        border.width: 1
        border.color: "#000000"

        PullOutMenuElement {
            id:orderButton
            nameText: qsTr("Orders") + langObject.emptyString
            height: mainMenuLayout.menuItemHeight

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
            name: "Hidden"
            AnchorChanges {
                    target: dragMenu
                    anchors.right: mainMenuLayout.left
                    anchors.left: undefined
                }
        },

        State {
            name: "Open"
            AnchorChanges {
                    target: dragMenu
                    anchors.right: undefined
                    anchors.left: mainMenuLayout.left
                }
        }
    ]

    transitions: [
        Transition {
            AnchorAnimation { duration: 500 }
        }
    ]
}
