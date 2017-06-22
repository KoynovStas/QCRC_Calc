import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3





Item {

    width: 780
    height: 80


    function set_crc_result(result) {

        for(var i = 0; i < byte_4_7.count; ++i) {
            byte_0_3.itemAt(i).set_crc_result(result)
            byte_4_7.itemAt(i).set_crc_result(result)
        }
    }


    RowLayout {
        id: layout
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        spacing: 15

        Repeater {
            id: byte_4_7
            model: [56, 48, 40, 32]

            ByteItem{ start_bit: modelData }
        }
    }


    RowLayout {
        id: layout2
        anchors.top: layout.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 5

        spacing: 15

        Repeater {
            id: byte_0_3
            model: [24, 16, 8, 0]

            ByteItem { start_bit: modelData }
        }
    }

}
