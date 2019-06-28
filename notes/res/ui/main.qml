import QtQuick 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Tabs")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        PageLeft {
        }

        PageRight {
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: "Left Page"
        }
        TabButton {
            text: "Right Page"
        }
    }
}
