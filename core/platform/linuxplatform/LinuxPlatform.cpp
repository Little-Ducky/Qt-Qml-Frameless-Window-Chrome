#include "LinuxPlatform.h"

LinuxPlatform::LinuxPlatform(QWindow *parent)
    : Platform(parent)
{

}

bool LinuxPlatform::nativeEvent(const QByteArray& eventType,
                                void *message,
                                qintptr *result)
{
    return QQuickWindow::nativeEvent(eventType, message, result);
}

bool LinuxPlatform::event(QEvent *e)
{
    switch (e->type())
    {
    case QEvent::MouseMove:
    {
        auto *me = static_cast<QMouseEvent *>(e);

        const Qt::Edges edges = LinuxUtils::resizeEdges(me->position(), size());

        if (edges == (Qt::LeftEdge | Qt::TopEdge) ||
            edges == (Qt::RightEdge | Qt::BottomEdge))
        {
            setCursor(Qt::SizeFDiagCursor);
            me->accept();
            return true;
        }

        if (edges == (Qt::RightEdge | Qt::TopEdge) ||
            edges == (Qt::LeftEdge | Qt::BottomEdge))
        {
            setCursor(Qt::SizeBDiagCursor);
            me->accept();
            return true;
        }

        if (edges & (Qt::LeftEdge | Qt::RightEdge))
        {
            setCursor(Qt::SizeHorCursor);
            me->accept();
            return true;
        }

        if (edges & (Qt::TopEdge | Qt::BottomEdge))
        {
            setCursor(Qt::SizeVerCursor);
            me->accept();
            return true;
        }

        unsetCursor();
        break;
    }

    case QEvent::MouseButtonPress:
    {
        auto *me = static_cast<QMouseEvent *>(e);

        if (me->button() != Qt::LeftButton)
            break;

        const Qt::Edges edges = LinuxUtils::resizeEdges(me->position(), size());

        if (edges)
        {
            startSystemResize(edges);
            me->accept();
            return true;
        }

        const QPointF pt = me->position();

        if (pt.y() < m_captionController->height() &&
            !m_captionController->findInteractiveAt(
                contentItem(),
                pt.toPoint()))
        {
            startSystemMove();
            me->accept();
            return true;
        }

        break;
    }

    case QEvent::MouseButtonDblClick:
    {
        auto *me = static_cast<QMouseEvent *>(e);

        const Qt::Edges edges = LinuxUtils::resizeEdges(me->position(), size());

        if (edges)
        {
            me->accept();
            return true;
        }

        const QPointF pt = me->position();

        if (me->button() == Qt::LeftButton &&
            pt.y() < m_captionController->height() &&
            !m_captionController->findInteractiveAt(
                contentItem(),
                pt.toPoint()))
        {
            m_windowController->toggleMaximized();
            me->accept();
            return true;
        }

        break;
    }

    default:
        break;
    }

    return QQuickWindow::event(e);
}

void LinuxPlatform::setup()
{
    setFlags(Qt::Window | Qt::FramelessWindowHint);

    const QRect screenGeometry =
        screen()->availableGeometry();

    setPosition(
        screenGeometry.x()
            + (screenGeometry.width() - width()) / 2,
        screenGeometry.y()
            + (screenGeometry.height() - height()) / 2);
}