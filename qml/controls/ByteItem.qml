import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3





Item {

    property int start_bit
    height: layout.height

    function set_crc_result(result) {

        for(var i = 0; i < bits.count; ++i)
            bits.itemAt(i).set_crc_result(result)
    }


    RowLayout {
        id: layout
        spacing: 6

        Repeater {
            id: bits
            model: [7, 6, 5, 4, 3, 2, 1, 0] //first bit has index 0

            BitItem {
                Layout.fillWidth: true
                num_bit: start_bit + modelData
            }
        }
    }
}
