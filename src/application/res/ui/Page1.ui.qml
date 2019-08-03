import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    id: page
    width: 600
    height: 400

    header: Label {
        text: "Page 1"
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        text: "You are on Page 1."
        anchors.verticalCenterOffset: -164
        anchors.horizontalCenterOffset: -226
        anchors.centerIn: parent
    }

    Dial {
        id: dial
        x: 33
        y: 23
        width: 113
        height: 109
        anchors.verticalCenterOffset: -23
        anchors.horizontalCenterOffset: 1
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: false
    }

    ProgressBar {
        id: progressBar
        x: 200
        y: 234
        wheelEnabled: false
        anchors.verticalCenterOffset: 66
        anchors.horizontalCenterOffset: 1
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        value: dial.value
    }
}
