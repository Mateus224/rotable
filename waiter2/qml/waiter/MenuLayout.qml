import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

ColumnLayout {
    id: menuLayout
    clip: true
    Layout.fillWidth: false
    anchors.bottomMargin: 0
    anchors.bottom: parent.bottom
    anchors.top: parent.top
    anchors.topMargin: 0
    spacing: 15
    
    Layout.fillHeight: true
    
    anchors.margins: margin
    
    GroupBox {
        id: rowBox
        Layout.fillHeight: false
        Layout.fillWidth: true
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        title: qsTr("Menu")
        //Layout.fillWidth: true

        ColumnLayout {
            id: rowLayout
            anchors.fill: parent
            Button {
                text: qsTr("Log out")
                Layout.fillWidth: true
                onClicked: waiter.logOff()
            }
            Button {
                text: qsTr("Settings")
                Layout.fillWidth: true
                enabled: false
            }
            Button {
                text: qsTr("Exit")
                Layout.fillWidth: true
                onClicked: Qt.quit()
            }
        }
    }

    //                GroupBox {
    //                    id: gridBox
    //                    title: qsTr("Table list")
    //                    Layout.fillWidth: true
    //                    height: {
    //                        if(tables.count == 0){
    //                            0;
    //                        }
    //                        else{
    //                            tableList.implicitHeight;
    //                        }
    //                    }
    
    //                    GridLayout {
    //                        id: gridLayout
    //                        rows: 2
    //                        flow: GridLayout.LeftToRight
    //                        Layout.fillWidth: true
    Label{
        id: tableMenuLabel
        text: qsTr("Table list")
        Layout.fillHeight: false
        Layout.fillWidth: true
        anchors.top: rowBox.bottom
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
    }
    
    ListView {
        id: tableList
        height: 200
        Layout.preferredWidth: 2
        Layout.fillWidth: true
        anchors.top: tableMenuLabel.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.leftMargin: 0
        Layout.fillHeight: true
        //height: implicitHeight
        //height: tableList.count * (spacing + 50)
        Layout.minimumWidth: 200
        spacing: margin
        
        ExclusiveGroup {
            id: tableExclusiveGroup
        }
        
        model: tables
        
        delegate: Button{
            id: tableListButton
            
            enabled: model.orderNumber == 0 ? false : true
            
            width:  parent.width
            checkable: true
            exclusiveGroup: tableExclusiveGroup
            property var connected: model.isConnected ? "Connected" : "Disconnected"
            x: 130
            y: 219
            text: "Table: " + model.name + ", " + model.id + "\nOrders: " + model.orderNumber + "\n" + connected
            anchors.horizontalCenter: parent.horizontalCenter
            
            onClicked: tables.sendToBoardOrder(model.id)
        }
    }
    //}
    //  }
    
    
}
