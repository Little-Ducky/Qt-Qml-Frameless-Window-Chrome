#include "../AppMainWindow.h"

// macOS implementation of AppMainWindow
// Currently uses the native macOS window title bar and window behavior (standard system chrome).
// In the future, this implementation may also be overridden to support a fully custom title bar,
// similar to the Windows frameless implementation.
AppMainWindow::AppMainWindow(QWindow *parent)
    : QQuickWindow(parent)
{
}

// Native event handler is currently not customized on macOS.
// All system events are handled by the default QQuickWindow implementation.
bool AppMainWindow::nativeEvent(const QByteArray& eventType,
                                void *message,
                                qintptr *result)
{
    return QQuickWindow::nativeEvent(eventType, message, result);
}

// Placeholder for future macOS-specific initialization logic.
void AppMainWindow::setup()
{
}
