import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3



Item {

    property int start_bit
    height: layout.height

    RowLayout {
        id: layout
        spacing: 6

        Repeater {
            model: 8
            BitItem {
                Layout.fillWidth: true
                label.text: (7+start_bit) - model.index  //7 (first bit has index 0)
            }
        }
    }
}
