import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
//import QtQuick.Controls.Material 2.1
import "./controls"





Frame {
    id: root

    width: 840
    height: 480

    topPadding: 0


    RowLayout {
        id: layout

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 45


        Label {
            id: label

            text: qsTr("Encoding:")

            anchors.left: layout.left

            bottomPadding: 10
            rightPadding: 10
        }


        ComboBox {
            id: comboBox

            anchors.left: label.right

            Layout.bottomMargin: 10
            Layout.minimumWidth: 290
            Layout.maximumWidth: 300

            model: calc_text.encodings

            currentIndex: calc_text.encoding_index

            onCurrentIndexChanged: calc_text.encoding_index = currentIndex
        }


        CheckBox {
            id: checkBox2

            text: qsTr("BOM")

            anchors.top: parent.top
            anchors.left: comboBox.right

            leftPadding: 20

            checked: calc_text.BOM

            onCheckedChanged: calc_text.BOM = checked
        }


        Label {
            id: label1

            text: qsTr("EndLine:")

            anchors.left: checkBox2.right

            bottomPadding: 10
            rightPadding: 10
        }


        ComboBox {
            id: comboBox1

            anchors.left: label1.right
            Layout.bottomMargin: 10
            Layout.minimumWidth: 150
            Layout.maximumWidth: 200


            model: calc_text.end_line_names

            currentIndex: calc_text.end_line_index

            onCurrentIndexChanged: calc_text.end_line_index = currentIndex
        }


        CheckBox {
            id: checkBox3

            text: qsTr("Wrap word")

            anchors.top: parent.top
            anchors.right: layout.right


            onCheckedChanged: {
                hex_text.textArea.wrapMode = checked ? TextEdit.WordWrap : TextEdit.NoWrap;
                hex_text.textArea.width = hex_text.flickable.width;
            }
        }

    }


    ScrollTextArea {
        id: hex_text

        anchors.top:    layout.bottom
        anchors.bottom: parent.bottom
        anchors.left:   parent.left
        anchors.right:  parent.right


        textArea.onTextChanged: calc_text.calculate(textArea.text)
    }

}
