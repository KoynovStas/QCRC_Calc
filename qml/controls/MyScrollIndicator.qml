import QtQuick 2.8
import QtQuick.Controls 2.1



Item {
    id: root

    // The properties that define the scrollbar's state.
    // position and pageSize are in the range 0.0 - 1.0.  They are relative to the
    // height of the page, i.e. a pageSize of 0.5 means that you can see 50%
    // of the height of the view.
    // orientation can be either Qt.Vertical or Qt.Horizontal
    property real position
    property real pageSize
    property int  orientation : Qt.Vertical
    property int  minimumSize : 50

    property alias background: background
    property alias indicator: indicator

    visible: pageSize < 1.0 ? true : false

    // A light, semi-transparent background
    Rectangle {
        id: background

        anchors.fill: parent

        color: "white"
        opacity: 0.3
    }

    // Size the bar to the required size, depending upon the orientation.
    Rectangle {
        id: indicator

        color: "gray"
        opacity: 0.7

        x: orientation == Qt.Vertical ? 1 : Math.min(root.position * root.width, root.width - minimumSize)
        y: orientation == Qt.Vertical ? Math.min(root.position * root.height, root.height - minimumSize) : 1

        width: orientation == Qt.Vertical ? parent.width : Math.max((root.pageSize * root.width), minimumSize)
        height: orientation == Qt.Vertical ? Math.max((root.pageSize * root.height), minimumSize) : parent.height
    }
}
