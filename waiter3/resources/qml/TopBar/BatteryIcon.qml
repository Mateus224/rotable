import QtQuick 2.5

Rectangle {
    id:iconBody

    property int batteryCheckInterval: 5000

    anchors.top: parent.top
    anchors.right: parent.right
    width: parent.width * 0.08
    height: parent.height

    Image {
        id: batteryImage
        anchors.fill: parent
        source: if (batteryInfo.batteryStatus>90) "qrc:/resources/images/Batteries/battery-full.svg"
                else if (batteryInfo.batteryStatus>70) "qrc:/resources/images/Batteries/battery-80.svg"
                else if (batteryInfo.batteryStatus>50) "qrc:/resources/images/Batteries/battery-60.svg"
                else if (batteryInfo.batteryStatus>30) "qrc:/resources/images/Batteries/battery-40.svg"
                else if (batteryInfo.batteryStatus>10) "qrc:/resources/images/Batteries/battery-20.svg"
                else "qrc:/resources/images/Batteries/battery-nul.svg"
        fillMode: Image.PreserveAspectFit
    }

    Timer {
        id: timer
        interval: batteryCheckInterval
        repeat: true
        running: true

        onTriggered:
        {
            if (batteryInfo.batteryStatus>90) batteryImage.source = "qrc:/resources/images/Batteries/battery-full.svg"
            else if (batteryInfo.batteryStatus>70) batteryImage.source = "qrc:/resources/images/Batteries/battery-80.svg"
            else if (batteryInfo.batteryStatus>50) batteryImage.source = "qrc:/resources/images/Batteries/battery-60.svg"
            else if (batteryInfo.batteryStatus>30) batteryImage.source = "qrc:/resources/images/Batteries/battery-40.svg"
            else if (batteryInfo.batteryStatus>10) batteryImage.source = "qrc:/resources/images/Batteries/battery-20.svg"
            else batteryImage.source = "qrc:/resources/images/Batteries/battery-nul.svg"
        }
    }
}
