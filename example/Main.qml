import QtQuick
import AppChrome 1.0

AppChrome {
    id: window

    width: 640
    height: 480

    title: qsTr("My custom caption example")

    caption: Component {
        CustomCaption {}
    }
}

