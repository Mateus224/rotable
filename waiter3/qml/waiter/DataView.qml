import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Rectangle {

    id: dataMain

    state: "Tables"

    TablesView {
        id: tablesView

        anchors.topMargin: 10
        anchors.fill: parent
    }
}
