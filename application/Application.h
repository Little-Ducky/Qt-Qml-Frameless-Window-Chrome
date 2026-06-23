#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>

#include "appmainwindow/AppMainWindow.h"

namespace Application {

// Registers AppMainWindow as a QML type.
// This currently overrides and customizes window behavior only on Windows,
// where native window events are intercepted and replaced with custom logic
// (frameless window, custom title bar, resize handling, system menu, etc.).
// On other platforms, default behavior is used.
inline void registerUiTypes()
{
    qmlRegisterType<AppMainWindow>(
        QML_MODULE,
        1, 0,
        "AppMainWindow"
        );
}

}

#endif // APPLICATION_H

