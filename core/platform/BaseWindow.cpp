#include "BaseWindow.h"

BaseWindow::BaseWindow(QWindow *parent)
    : QQuickWindow(parent)
    , m_captionController(new CaptionController(this))
    , m_windowController(new WindowController(this))
{
}

CaptionController* BaseWindow::captionController() const
{
    return m_captionController;
}

WindowController* BaseWindow::windowController() const
{
    return m_windowController;
}