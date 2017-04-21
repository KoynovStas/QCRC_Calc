import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import "./controls"



Frame {

    anchors.left: parent.left
    anchors.right: parent.right
    bottomPadding: 0


    ColumnLayout {

        anchors.fill: parent

        spacing: 1


        RowLayout {
            id: layout1

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            spacing: 10


            MyTextEdit {
                id: hex_res
                label.text: "Hex:"

                textField.readOnly: true
                textField.implicitWidth: 210
            }

            MyTextEdit {
                id: dec_res
                label.text: "Dec:"

                textField.readOnly: true
                textField.implicitWidth: 210
            }

            MyTextEdit {
                id: oct_res
                label.text: "Oct:"

                textField.text: "1262037334654760060066"
                textField.readOnly: true
                textField.implicitWidth: 210
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
                textField.text: "0xFFFFFF"
                textField.implicitWidth: 600
            }


            SpinBox2d {

                to: 36
                from: 2
                value: 2

                anchors.left: base_edit.right

                Layout.preferredWidth: 140
                Layout.minimumWidth: 140
                Layout.leftMargin: 10
            }

        }


        BitSet64 {
//            Layout.fillWidth: false
//            anchors.top: layout2.bottom

//            anchors.topMargin: 5
//            anchors.left: parent.left
//            anchors.right: parent.right
        }
    }
}
