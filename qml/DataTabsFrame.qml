import QtQuick 2.8
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

        Repeater {
            model: listTabs
            delegate:Loader {
                source: model.source;
            }
        }
    }



//    footer:TabBar {
    header:TabBar {
        id: tabBar
        implicitHeight: 35
        currentIndex: swipeView.currentIndex
//        background: Rectangle {
//                  color: "#eeeeee"
//              }

        Repeater {
            model: listTabs

            TabButton {
                implicitHeight: 35
                text: model.title
            }
        }
    }

}
