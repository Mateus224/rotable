import QtQuick 2.0

Rectangle {
    id: mainScreen

    Rectangle {
        id: screen
        width: Math.min(parent.height, parent.width)
        height: Math.min(parent.height, parent.width)

        TableList{
            id: tableList
        }
    }
}

