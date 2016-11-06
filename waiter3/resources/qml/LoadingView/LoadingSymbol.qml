import QtQuick 2.5

Rectangle {

    id: symbol

    property color maxGray: "#FF101010"
    property color gray2: "#b0101010"
    property color gray1: "#70101010"
    property color minGray: "#20101010"

    width: (parent.width * 0.05) > 600 ? 400 : parent.width * 0.05
    height: (parent.width * 0.05) > 600 ? 400 : parent.width * 0.05

    property int maxPoints: 8
    property int circleRadius: width

    color: "#00FFFFFF"

    LoadDot {
        id: dot1
        position: 0
        counter: 0
    }
    LoadDot {
        id: dot2
        position: 1
        counter: 1
    }
    LoadDot {
        id: dot3
        position: 2
        counter : 2
    }
    LoadDot {
        id: dot4
        position: 3
        counter: 3
    }
    LoadDot {
        id: dot5
        position: 4
        counter: 4
    }
    LoadDot {
        id: dot6
        position: 5
        counter: 5
    }
    LoadDot {
        id: dot7
        position: 6
        counter: 6
    }
    LoadDot {
        id: dot8
        position: 7
        counter: 7
    }

    Timer {
        id: timer
        interval: 100
        repeat: true
        running: symbol.opacity==1

        onTriggered:
        {
            if (--dot1.counter < 0) dot1.counter=maxPoints-1;
            if (--dot2.counter < 0) dot2.counter=maxPoints-1;
            if (--dot3.counter < 0) dot3.counter=maxPoints-1;
            if (--dot4.counter < 0) dot4.counter=maxPoints-1;
            if (--dot5.counter < 0) dot5.counter=maxPoints-1;
            if (--dot6.counter < 0) dot6.counter=maxPoints-1;
            if (--dot7.counter < 0) dot7.counter=maxPoints-1;
            if (--dot8.counter < 0) dot8.counter=maxPoints-1;
        }
    }

}
