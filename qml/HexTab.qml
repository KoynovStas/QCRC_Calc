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

            onCheckedChanged: calc_hex.revers_chunk = checked
        }


        CheckBox {
            id: checkBox2

            text: qsTr("Revers data")

            anchors.top: parent.top
            anchors.left: checkBox.right

            bottomPadding: 20

            checked: calc_hex.revers_data

            onCheckedChanged: calc_hex.revers_data = checked
        }


        CheckBox {
            id: checkBox3

            text: qsTr("Wrap word")

            anchors.top: parent.top
            anchors.right: layout.right

            bottomPadding: 20


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
    }

}
