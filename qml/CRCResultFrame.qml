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
    bottomPadding: 0


    background: Rectangle {
        anchors.fill: parent
        anchors.topMargin: 26
        anchors.bottomMargin: 5

        visible: (hexBtn.checked || baseBtn.checked || bitsBtn.checked)

        color: "transparent"
        border.color: "darkgray"
    }



    ColumnLayout {
        anchors.fill: parent

        RowLayout {

            StatusBar {
                id: statusBar
                Layout.fillWidth: true
            }

            CheckableButton {
                id: hexBtn
                text: qsTr("Hex")
                checked: true
            }

            CheckableButton {
                id: baseBtn
                text: qsTr("Base")
            }

            CheckableButton {
                id: bitsBtn
                text: qsTr("Bits")
            }
        }



        RowLayout {
            Layout.fillWidth: true
            Layout.bottomMargin: 8

            visible: hexBtn.checked

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
            Layout.fillWidth: true
            visible: baseBtn.checked
            spacing: 10

            MyTextEdit {
                id: base_edit
                alignment: Qt.AlignRight

                width: 620

                label.text: "Base:"

                textField.readOnly: true
                textField.text: crc_result.result_base
            }


            SpinBox2d {
                Layout.preferredWidth: 140
                Layout.minimumWidth: 140
                Layout.leftMargin: 10

                to: 36
                from: 2
                value: crc_result.base

                onValueChanged: crc_result.base = value
            }
        }



        BitSet64 {
            id: bitSet

            visible: bitsBtn.checked

            Connections {
                target: crc_result
                function onResultChanged() { bitSet.set_crc_result(crc_result) }
            }
        }

    } //ColumnLayout
}
