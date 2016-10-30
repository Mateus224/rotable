import QtQuick 2.5

Rectangle {

    id: symbol

    property color maxGray: "#FF101010"
    property color gray2: "#c0101010"
    property color gray1: "#80101010"
    property color minGray: "#40101010"

    width: (parent.width * 0.04) > 600 ? 400 : parent.width * 0.04
    height: (parent.width * 0.04) > 600 ? 400 : parent.width * 0.04

    LoadDot {
        id: dot1
        position: 0
        color: maxGray
    }
    LoadDot {
        id: dot2
        position: 1
        color: gray2
    }
    LoadDot {
        id: dot3
        position: 2
        color: gray1
    }
    LoadDot {
        id: dot4
        position: 4
        color: minGray
    }
    LoadDot {
        id: dot5
        position: 5
        color: minGray
    }
    LoadDot {
        id: dot6
        position: 6
        color: minGray
    }
    LoadDot {
        id: dot7
        position: 7
        color: minGray
    }
    LoadDot {
        id: dot8
        position: 8
        color: minGray
    }


}
