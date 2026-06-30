import QtQuick 2.15
import QtQuick.Layouts
import QtQuick.Controls

BaseCaption {
    id: root

    property bool compact: width < 620
    property bool firstStart: true

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#2A0F14" }
        GradientStop { position: 0.5; color: "#3A1418" }
        GradientStop { position: 1.0; color: "#220B0F" }
    }

    Component.onCompleted: {
        firstStart = false
    }

    states: [
        State {
            name: "normal"
            when: !compact

            AnchorChanges {
                target: titleLabel
                anchors.left: undefined
                anchors.horizontalCenter: parent.horizontalCenter
            }

            PropertyChanges {
                target: titleLabel
                anchors.leftMargin: 0
                font.pixelSize: 16
            }
        },

        State {
            name: "compact"
            when: compact

            AnchorChanges {
                target: titleLabel
                anchors.horizontalCenter: undefined
                anchors.left: parent.left
            }

            PropertyChanges {
                target: titleLabel
                anchors.leftMargin: 12
                font.pixelSize: 13
            }
        }
    ]

    transitions: Transition {
        enabled: !firstStart

        AnchorAnimation {
            duration: 180
            easing.type: Easing.InOutCubic
        }

        NumberAnimation {
            properties: "anchors.leftMargin,font.pixelSize"
            duration: 180
            easing.type: Easing.InOutCubic
        }
    }

    Label {
        id: titleLabel

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        text: window.title

        font.pixelSize: 16
        font.bold: true
        color: "#F4E8FF"
    }

    RowLayout {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 6

        spacing: root.compact ? 2 : 6

        CustomCaptionButton {
            text: window.visibility === Window.Maximized ? "⧉" : "⛶"
            Layout.preferredWidth: root.compact ? 28 : 36
            Layout.fillHeight: true
            onClicked: window.windowController.toggleMaximized()
        }

        CustomCaptionButton {
            text: "—"
            Layout.preferredWidth: root.compact ? 28 : 36
            Layout.fillHeight: true
            onClicked: window.windowController.showMinimized()
        }

        CustomCaptionButton {
            text: "✕"
            Layout.preferredWidth: root.compact ? 28 : 36
            Layout.fillHeight: true
            onClicked: window.windowController.close()
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 1
        color: "#5a1a1f"
        opacity: 0.8
    }
}