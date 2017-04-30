import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3





Item {

    property alias label: label

    function set_status(msg, isError) {
        label.text = msg

        label.color = isError ? "red" : "black"
    }


    height: 16

    anchors.bottomMargin: 5


    Label {
        id: label

        text: "No data"
    }

}
