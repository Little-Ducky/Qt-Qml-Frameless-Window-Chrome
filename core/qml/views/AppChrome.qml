import QtQuick 2.15

AppMainWindow {
    id: root

    property Component caption: defaultCaption

    visible: false

    Component {
        id: defaultCaption

        DefaultAppCaption {
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: "#26133D"
                }

                GradientStop {
                    position: 0.5
                    color: "#1D102F"
                }

                GradientStop {
                    position: 1.0
                    color: "#130A22"
                }
            }
        }
    }

    Loader {
        id: captionLoader
        sourceComponent: root.caption
    }

    Component.onCompleted: {
        // Performs platform-specific window initialization.
        root.setup()

        root.visible = true
    }
}
