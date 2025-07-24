import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3




Page {


    ListModel {
        id: listTabs
        ListElement { title: "Hex";  source: "qrc:/qml/HexTab.qml"  }
        ListElement { title: "Text"; source: "qrc:/qml/TextTab.qml" }
    }


    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        interactive: false


        Repeater {
            model: listTabs

            delegate:Loader {
                source: model.source;
            }
        }

    }


    header:TabBar {
        id: tabBar
        implicitHeight: 35
        currentIndex: swipeView.currentIndex

        Repeater {
            model: listTabs

            TabButton {
                implicitHeight: 35
                text: model.title
            }
        }
    }
}
