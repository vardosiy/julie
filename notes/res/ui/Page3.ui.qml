import QtQuick 2.11
import QtQuick.Controls 2.4

Page {
    width: 600
    height: 400

    header: Label {
        text: "IZI"
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        text: "Hello Bitch"
        anchors.centerIn: parent
    }
}
