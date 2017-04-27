import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
//import QtQuick.Controls.Material 2.1
import "./controls"




Frame {
    id: root

    width: 640
    height: 480

    topPadding: 0
    bottomPadding: 0


    function calculate() {
            calc_hex.calculate(text_data.textArea.text)
        }



    RowLayout {
        id: layout

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 45


        CheckBox {
            id: checkBox

            text: qsTr("Revers word")

            anchors.top: parent.top

            bottomPadding: 20

            checked: calc_hex.revers_chunk

            onCheckedChanged: {

                calc_hex.revers_chunk = checked
                calculate()
            }
        }


        CheckBox {
            id: checkBox2

            text: qsTr("Revers data")

            anchors.top: parent.top
            anchors.left: checkBox.right

            bottomPadding: 20

            checked: calc_hex.revers_data

            onCheckedChanged: {

                calc_hex.revers_data = checked
                calculate()
            }
        }


        CheckBox {
            id: checkBox3

            text: qsTr("Wrap word")

            anchors.top: parent.top
            anchors.right: layout.right

            bottomPadding: 20


            onCheckedChanged: {
                text_data.textArea.wrapMode = checked ? TextEdit.WordWrap : TextEdit.NoWrap;
                text_data.textArea.width = text_data.flickable.width;
            }
        }
    }



    ScrollTextArea {
        id: text_data

        anchors.top:    layout.bottom
        anchors.bottom: result_frame.top
        anchors.left:   parent.left
        anchors.right:  parent.right

        anchors.bottomMargin: 10 //need for ScrollBar

        textArea.onTextChanged: calculate()
    }


    CRCResultFrame {
        id: result_frame

        crc_result: calc_hex.result

        Layout.fillWidth: true
        anchors.bottom: parent.bottom
    }

}
