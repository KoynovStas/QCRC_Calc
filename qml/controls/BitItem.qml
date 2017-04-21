import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3



Item {

    property bool value
    property alias label: label

    width: rect.width
    height: rect.height + label.paintedHeight


    Rectangle {
        id: rect

        width: 16
        height: 16

        border.width: 2
        border.color: "#3C3C3C"

        color: value ? "#3C3C3C" : "transparent"
    }


    Label {
        id: label

        anchors.horizontalCenter: rect.horizontalCenter
        anchors.top: rect.bottom
    }
}
