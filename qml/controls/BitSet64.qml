import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3



Item {

    width: 780
    height: 80

//    color: "green"


    RowLayout {
        id: layout
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        spacing: 15

        ByteItem{
            start_bit: 56
        }

        ByteItem{
            start_bit: 48
        }

        ByteItem{
            start_bit: 40
        }

        ByteItem{
            start_bit: 32
        }
     }

    RowLayout {
        id: layout2
        anchors.top: layout.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 5

        spacing: 15

        ByteItem{
            start_bit: 24
        }

        ByteItem{
            start_bit: 16
        }

        ByteItem{
            start_bit: 8
        }

        ByteItem{
            start_bit: 0
        }
     }

}
