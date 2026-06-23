#include "AppWindowController.h"

AppWindowController::AppWindowController(QObject *parent)
    : QObject{parent},
    m_window{qobject_cast<QQuickWindow*>(parent)}
{
}

void AppWindowController::toggleFullscreen()
{
    if (m_window->visibility() == QWindow::FullScreen)
    {
        showNormal();
    }
    else
    {
        showFullScreen();
    }
}

void AppWindowController::showFullScreen()
{
    m_window->showFullScreen();
}

void AppWindowController::showMinimized()
{
    if (!(m_window->windowState() & Qt::WindowMinimized))
        m_prevState = m_window->windowState();

    m_window->showMinimized();
}

void AppWindowController::showMaximized()
{
    m_window->showMaximized();
}

void AppWindowController::showNormal()
{
    m_window->showNormal();

    if (m_prevState == Qt::WindowMaximized)
    {
        m_window->showMaximized();
    }

    m_prevState = Qt::WindowNoState;
}

void AppWindowController::close()
{
    m_window->close();
}
