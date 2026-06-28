#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>

#if defined(_WIN32)
#include "windowsplatform/WindowsPlatform.h"
using Platform = WindowsPlatform;
#elif defined(__APPLE__)
#include "macplatform/MacPlatform.h"
using Platform = MacPlatform;
#elif defined(__linux__)
#include "linuxplatform/LinuxPlatform.h"
using Platform = LinuxPlatform;
#endif

namespace Application {

// Registers AppMainWindow as a QML type.
void registerUiTypes()
{
    qmlRegisterType<Platform>(
        QML_MODULE,
        1, 0,
        "AppMainWindow"
        );
}
}
#endif // APPLICATION_H
