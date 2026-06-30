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
               control.hovered ? "#ffd6d6" :
               "#e0b3b3"

        font.pixelSize: 16
        font.bold: true

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        id: bg
        radius: 8

        color:
            control.down
            ? "#5a1a1f"
            : control.hovered
              ? "#3a1418"
              : "transparent"

        Behavior on color {
            ColorAnimation { duration: 140 }
        }

        Rectangle {
            id: borderRect
            anchors.fill: parent
            anchors.margins: 1

            radius: parent.radius - 1

            color: "transparent"

            border.width: 1

            border.color:
                control.hovered
                ? "#9a454a"
                : "#4a2a2c"

            Behavior on border.color {
                ColorAnimation { duration: 160 }
            }
        }
    }
}