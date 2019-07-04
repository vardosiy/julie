import QtQuick 2.9
import QtQuick.Controls 2.4

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Tabs"

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
        }
        Page2 {
        }
        Page3 {
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
        TabButton {
            text: "Page3"
        }
    }
}


