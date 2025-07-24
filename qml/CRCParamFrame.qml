import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1
import "./controls"




Frame {

    topPadding: 5


    ColumnLayout {
        anchors.fill: parent


        RowLayout {
            Layout.fillWidth: true
            spacing: 6


            ComboBox {
                id: crc_name_comboBox

                implicitWidth: 150
                Layout.minimumWidth: 200

                model: uCRC.crc_names

                currentIndex: uCRC.index

                onCurrentIndexChanged: uCRC.index = currentIndex
            }


            Label {
                text: "Bits (1..64):"

                rightPadding: 0
                leftPadding: 16

                verticalAlignment: Text.AlignVCenter
            }


            SpinBox2d {
                id: crc_bits_spinBox

                to: 64
                from: 1
                value: uCRC.bits

                onValueChanged: uCRC.bits = value

                Layout.maximumWidth: 120
                Layout.preferredWidth: 150
                Layout.minimumWidth: 150
            }


            CheckBox {
                id: crc_RefIn_checkBox

                text: qsTr("RefIn")

                checked: uCRC.ref_in

                onCheckedChanged: uCRC.ref_in = checked
            }


            CheckBox {
                id: crc_RefOut_checkBox

                text: qsTr("RefOut")

                checked: uCRC.ref_out

                onCheckedChanged: uCRC.ref_out = checked
            }

            ArrowButton {
                id: extParamBtn

                Layout.leftMargin: 50

                checked: true
            }

            ArrowButton {
                id: extInfoBtn
            }


            Item { // need only for force align ForkMe to right
                Layout.fillWidth: true
            }

            Button {
                Layout.rightMargin: -60

                implicitWidth: 150
                rotation: 45

                text: qsTr("Fork me")

                onPressed: Qt.openUrlExternally("https://github.com/KoynovStas/QCRC_Calc");
            }
        }



        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            visible: extParamBtn.checked


            MyTextEdit {
                label.text: "Poly(Hex):"

                textField.text: uCRC.poly_str

                textField.onTextChanged: uCRC.poly_str = textField.text
            }

            MyTextEdit {
                label.text: "Init(Hex):"

                textField.text: uCRC.init_str

                textField.onTextChanged: uCRC.init_str = textField.text
            }

            MyTextEdit {
                label.text: "XorOut(Hex):"

                textField.text: uCRC.xor_out_str

                textField.onTextChanged: uCRC.xor_out_str = textField.text
            }
        }



        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            visible: extInfoBtn.checked


            MyTextEdit {
                label.text: "Check(Hex):"

                textField.readOnly: true
                textField.text: uCRC.check_str
                textField.color: "gray"
            }

            MyTextEdit {
                label.text: "Mask(Hex):"

                textField.readOnly: true
                textField.text: uCRC.crc_mask_str
                textField.color: "gray"
            }

            MyTextEdit {
                label.text: "TopBit(Hex):"

                textField.readOnly: true
                textField.text: uCRC.top_bit_str
                textField.color: "gray"
            }
        }
    } //ColumnLayout
}
