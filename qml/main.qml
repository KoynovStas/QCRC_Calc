import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3





ApplicationWindow {
    id: win

    width: 800
    height: 580

    minimumWidth: 800

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


        DataTabsFrame {
            id: data_tabs

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 200

            anchors.top: crc_param.bottom
        }


        CRCResultFrame {
            id: crc_result

            Layout.fillWidth: true

            anchors.top: data_tabs.bottom
            anchors.bottom: parent.bottom
        }
    }
}
