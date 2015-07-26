import QtQuick 2.0

Rectangle {
    id: mainScreen

    Rectangle {
        id: screen
        width: parent.width
        height: parent.height

        color: "blue"

        Rectangle{
            id: leftSidebar

            // Set minimal size of left sidebar
            width: Math.max(100,parent.width/5)
            height: parent.heigh
            color: "lightblue"

            //Margin left
            anchors.left: parent.left
            anchors.leftMargin: 10

            //margin top
            anchors.top: parent.top
            anchors.topMargin: 10

            Menu{
                id: menu
            }

            TableList{
                id: tableList
            }
        }

        Rectangle{
            id: centerContent


            // Margin left
            anchors.left: leftSidebar.right
            anchors.leftMargin: 10

            //Margin top
            anchors.top: parent.top
            anchors.topMargin: 10

            //Margin bottom
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            //Margin right
            anchors.right: parent.right
            anchors.rightMargin: 10

            OrderList{
                id: orderList
            }
        }

    }
}

