import QtQuick
import QtQuick.Controls

ToolButton {
    id: control

    implicitWidth: 42
    implicitHeight: 32

    hoverEnabled: true

    contentItem: Text {
        text: control.text
        color: control.down ? "#ffffff" :
               control.hovered ? "#f0d7ff" :
               "#d7b8ff"

        font.pixelSize: 16
        font.bold: true

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        radius: 8

        color:
            control.down
            ? "#8d3dff"
            : control.hovered
              ? "#6120c8"
              : "transparent"

        Rectangle {
            anchors.fill: parent
            anchors.margins: 1

            radius: parent.radius - 1

            color: "transparent"

            border.width: 1
            border.color:
                control.hovered
                ? "#b266ff"
                : "#6020b020"
        }
    }
}