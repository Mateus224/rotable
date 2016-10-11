import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

ListView {
    Label{
        id: labelneedList
        text: qsTr("Table need waiter")
        //                anchors.top: tableList.bottom
        //                anchors.horizontalCenter: parent.horizontalCenter
    }
    id: needList
    height: 200
    Layout.fillWidth: true
    //                anchors.top: labelneedList.bottom
    //                anchors.right: parent.right
    //                anchors.left: parent.left
    //                anchors.leftMargin: 0
    Layout.fillHeight: false
    //height: implicitHeight
    //height: tableList.count * (spacing + 50)
    Layout.minimumWidth: 200
    spacing: margin
    
    model: needBoard
    
    delegate: Button{
        id: needBoardButton
        width:  parent.width
        text: "Table " + model.tableName
        
        onClicked: needBoard.unneedTable(model.tableIdx)
    }
}
