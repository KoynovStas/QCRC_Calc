import QtQuick 2.6
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
        calc_text.calculate(text_data.textArea.text)
    }


    RowLayout {
        id: layout

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 45


        Label {
            id: label

            text: qsTr("Encoding:")

            bottomPadding: 10
            rightPadding: 10
        }


        ComboBox {
            id: comboBox

            Layout.bottomMargin: 10
            Layout.minimumWidth: 290
            Layout.maximumWidth: 300

            model: calc_text.encodings

            currentIndex: calc_text.encoding_index

            onCurrentIndexChanged: {
                calc_text.encoding_index = currentIndex
                calculate()
            }
        }


        CheckBox {
            id: checkBox2

            text: qsTr("BOM")

            leftPadding: 20
            bottomPadding: 25

            checked: calc_text.BOM

            onCheckedChanged: {
                calc_text.BOM = checked
                calculate()
            }
        }


        Label {
            id: label1

            text: qsTr("EndLine:")

            bottomPadding: 10
            rightPadding: 10
        }


        ComboBox {
            id: comboBox1

            Layout.bottomMargin: 10
            Layout.minimumWidth: 160
            Layout.maximumWidth: 200


            model: calc_text.end_line_names

            currentIndex: calc_text.end_line_index

            onCurrentIndexChanged: {
                calc_text.end_line_index = currentIndex
                calculate()
            }
        }


        Item { // need only for force align comboBox1 to left
            Layout.fillWidth: true
        }


        CheckBox {
            id: checkBox3

            text: qsTr("Wrap word")

            Layout.alignment: Qt.AlignRight
            bottomPadding: 25

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

        crc_result: calc_text.result

        Layout.fillWidth: true

        anchors.bottom: parent.bottom
    }


    Connections {
        target: uCRC
        onParamChanged: calculate()
    }


    Connections {
        target: calc_text
        onCalculated: result_frame.statusBar.set_status("Bytes: " + calc_text.get_num_bytes() +
                                                        " Lines: " + calc_text.get_num_lines(), false)

        onError: result_frame.statusBar.set_status(err, true)
    }
}
