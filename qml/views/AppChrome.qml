import QtQuick 2.15

AppMainWindow {
    id: window

    visible: false

    // Temporary: custom caption is currently implemented only on Windows.
    // Other platforms continue using their native window decorations.
    Loader {
        id: captionLoader
        active: Qt.platform.os === "windows"
        sourceComponent: AppCaption {}
    }

    Component.onCompleted: {
        // Performs platform-specific window initialization.
        window.setup()

        window.visible = true
    }
}
