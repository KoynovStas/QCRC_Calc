import QtQuick 2.8
import QtQuick.Controls 2.1





ApplicationWindow {
    id: win

    width: 800
    height: 580

    minimumWidth: 800

    title: qsTr("Hello World")
    visible: true

    Rectangle {
        anchors.fill: parent
    }
}
