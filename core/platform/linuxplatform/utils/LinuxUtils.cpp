#include "LinuxUtils.h"

LinuxUtils::LinuxUtils() {}

Qt::Edges LinuxUtils::resizeEdges(const QPointF &pos, const QSizeF& size)
{
    constexpr qreal border = WindowConstants::ResizeBorder;

    Qt::Edges edges;

    if (pos.x() <= border)
        edges |= Qt::LeftEdge;

    if (pos.x() >= size.width() - border)
        edges |= Qt::RightEdge;

    if (pos.y() <= border)
        edges |= Qt::TopEdge;

    if (pos.y() >= size.height() - border)
        edges |= Qt::BottomEdge;

    return edges;
}