import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3





Item {

    property int num_bit
    property bool value
    property alias label: label

    width: rect.width
    height: rect.height + label.paintedHeight


    function set_crc_result(result) {
        value = result.get_result_bit(num_bit)
    }


    Rectangle {
        id: rect

        width: 16
        height: 16

        border.width: 2
        border.color: "#3C3C3C"

        color: value ? "#3C3C3C" : "transparent"
    }


    Label {
        id: label

        text: num_bit
        anchors.horizontalCenter: rect.horizontalCenter
        anchors.top: rect.bottom
    }

}
