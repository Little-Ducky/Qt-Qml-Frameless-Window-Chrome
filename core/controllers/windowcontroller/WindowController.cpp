#include "WindowController.h"

WindowController::WindowController(QObject *parent)
    : QObject{parent},
    m_window{qobject_cast<QQuickWindow*>(parent)}
{
}

void WindowController::toggleMaximized()
{
    if (m_window->visibility() == QWindow::Maximized)
    {
        showNormal();
    }
    else
    {
        showMaximized();
    }
}

void WindowController::showFullScreen()
{
    m_window->showFullScreen();
}

void WindowController::showMinimized()
{
    if (!(m_window->windowState() & Qt::WindowMinimized))
        m_prevState = m_window->windowState();

    m_window->showMinimized();
}

void WindowController::showMaximized()
{
    m_window->showMaximized();
}

void WindowController::showNormal()
{
    m_window->showNormal();

    if (m_prevState == Qt::WindowMaximized)
    {
        m_window->showMaximized();
    }

    m_prevState = Qt::WindowNoState;
}

void WindowController::close()
{
    m_window->close();
}
