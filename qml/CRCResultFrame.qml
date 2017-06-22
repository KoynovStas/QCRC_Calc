import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import CRC_Calc 1.0
import "./controls"





Frame {

    property CRC_Result crc_result
    property alias statusBar: statusBar


    anchors.left: parent.left
    anchors.right: parent.right
    topPadding: 0


    background: Rectangle {
        anchors.fill: parent
        anchors.topMargin: 20

        color: "transparent"
        border.color: "darkgray"
    }



    ColumnLayout {

        anchors.fill: parent

        spacing: 1


        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            Layout.leftMargin: 0

            spacing: 10

            StatusBar {
                id: statusBar
            }
        }



        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            Layout.topMargin: 10


            spacing: 10


            MyTextEdit {
                id: hex_res
                label.text: "Hex:"

                width: 250
                textField.readOnly: true
                textField.implicitWidth: 210

                textField.text: crc_result.result_hex
            }

            MyTextEdit {
                id: dec_res
                label.text: "Dec:"
                width: 250
                textField.readOnly: true
                textField.implicitWidth: 210

                textField.text: crc_result.result_dec
            }

            MyTextEdit {
                id: oct_res
                label.text: "Oct:"

                width: 250
                textField.readOnly: true
                textField.implicitWidth: 210

                textField.text: crc_result.result_oct
            }

        }



        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right

            anchors.bottomMargin: 0


            MyTextEdit {
                id: base_edit

                anchors.left: parent.left
                alignment: Qt.AlignRight

                implicitWidth: 640

                label.text: "Base:"

                textField.readOnly: true
                textField.implicitWidth: 600

                textField.text: crc_result.result_base
            }


            SpinBox2d {

                to: 36
                from: 2
                value: crc_result.base

                onValueChanged: crc_result.base = value

                anchors.left: base_edit.right

                Layout.preferredWidth: 140
                Layout.minimumWidth: 140
                Layout.leftMargin: 10
            }

        }



        BitSet64 {
            id: bitSet

            Connections {
                target: crc_result
                onResultChanged: bitSet.set_crc_result(crc_result);
            }
        }

    } //ColumnLayout
}
