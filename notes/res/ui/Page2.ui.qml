import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    width: 600
    height: 400

    header: Label {
        text: "Page 2"
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        text: "You are on Page 2."
        anchors.centerIn: parent
    }

    ScrollView {
        id: scrollView
        x: 13
        y: 28
        width: 200
        height: 200
    }
}
