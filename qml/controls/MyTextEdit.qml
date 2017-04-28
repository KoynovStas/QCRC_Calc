import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3



//Rectangle {
Item {
    id: root

    width: 255
    height: 30

    property int alignment: Qt.AlignLeft

    property alias label: label
    property alias textField: textField

    //    color: "transparent"


    //    implicitWidth: Math.max(textField.implicitWidth + label.contentWidth, width)
    //    implicitHeight: Math.max(label.implicitHeight + topPadding + bottomPadding,
    //                             textField.implicitHeight + topPadding + bottomPadding)


    Label {
        id: label

        anchors.left: root.alignment == Qt.AlignLeft ? root.left : undefined
        anchors.right: root.alignment == Qt.AlignRight ? root.right : undefined
        anchors.verticalCenter: root.verticalCenter
    }

    TextField {
        id: textField

        anchors.left: root.alignment == Qt.AlignRight ? root.left : undefined
        anchors.right: root.alignment == Qt.AlignLeft ? root.right : undefined
        anchors.verticalCenter: root.verticalCenter

        Layout.fillWidth: root.Layout.fillWidth

        horizontalAlignment: Text.AlignLeft

        placeholderText: qsTr("Hex")
        selectByMouse: true
        implicitWidth: 165
    }
}
