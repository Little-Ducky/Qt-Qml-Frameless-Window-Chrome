import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

BaseCaption {
    RowLayout {
        anchors.fill: parent
        spacing: 8

        Label {
            text: root.title

            font.pixelSize: 18
            font.bold: true

            color: "#F4E8FF"

            leftPadding: 14
            rightPadding: 14

            Layout.fillHeight: true

            verticalAlignment: Text.AlignVCenter
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        DefaultCaptionButton {
            text: root.visibility === Window.Maximized ? "⧉" : "⛶"

            Layout.alignment: Qt.AlignVCenter
            Layout.fillHeight: true

            onClicked: root.windowController.toggleMaximized()
        }

        DefaultCaptionButton {
            text: "—"
            Layout.alignment: Qt.AlignVCenter
            Layout.fillHeight: true
            onClicked: root.windowController.showMinimized()
        }

        DefaultCaptionButton {
            text: "✕"
            Layout.alignment: Qt.AlignVCenter
            Layout.fillHeight: true
            onClicked: root.windowController.close()
        }
    }
}
