import QtQuick 2.0

Rectangle {
    id: mainScreen

    Rectangle {
        id: screen
        width: parent.width
        height: parent.height

        TableList{
            id: tableList
        }
    }
}

