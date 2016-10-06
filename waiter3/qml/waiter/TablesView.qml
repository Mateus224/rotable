import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {

    id: tablesMain

    property int orderListMargin: Math.max(10,width*0.35*0.04)

    TableList {
        id: tableList
        height: parent.height
        anchors.left: parent.left
    }

    OrderList {
        id: orderList
        height: parent.height
        anchors.left: tableList.right
        anchors.margins: orderListMargin
    }
}
