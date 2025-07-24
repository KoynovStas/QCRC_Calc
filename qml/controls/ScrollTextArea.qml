import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1




Item {

    property alias flickable: flickable
    property alias textArea: textArea


    Flickable {
        id: flickable

        anchors.fill: parent


        TextArea.flickable: TextArea {
            id: textArea

            selectByMouse: true
            renderType: Text.NativeRendering

            background: Rectangle {
                border.color: Material.color(Material.Grey)
            }
        }


        ScrollBar.vertical: ScrollBar {

            parent: flickable.parent
            anchors.top: flickable.top
            anchors.left: flickable.right
            anchors.bottom: flickable.bottom

            implicitWidth: 10

            opacity: 0.0
        }


        ScrollBar.horizontal: ScrollBar {

            parent: flickable.parent
            anchors.left: flickable.left
            anchors.right: flickable.right
            anchors.top: flickable.bottom

            implicitHeight: 10

            opacity: 0.0
        }

    }


    MyScrollIndicator {
        width: 8
        orientation: Qt.Vertical

        anchors.top: flickable.top
        anchors.left: flickable.right
        anchors.bottom: flickable.bottom

        position: flickable.visibleArea.yPosition
        pageSize: flickable.visibleArea.heightRatio
    }


    MyScrollIndicator {
        height: 8
        orientation: Qt.Horizontal

        anchors.left: flickable.left
        anchors.right: flickable.right
        anchors.top: flickable.bottom

        position: flickable.visibleArea.xPosition
        pageSize: flickable.visibleArea.widthRatio
    }
}
