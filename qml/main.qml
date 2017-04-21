import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3





ApplicationWindow {
    id: win

    width: 800
    height: 580

    minimumWidth: 800

    title: qsTr("Hello World")
    visible: true


    ColumnLayout {
        id: layout

        anchors.fill: parent
        spacing: 6


        CRCParamFrame {
            id: crc_param

            Layout.fillWidth: true

            anchors.top: parent.top
        }
    }
}
