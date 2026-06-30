import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

BaseCaption {
    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 32

            Item {
                Layout.preferredWidth: 80
            }

            Label {
                text: root.title

                Layout.fillWidth: true

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter

                font.pixelSize: 18
                font.bold: true
            }
        }
    }
}