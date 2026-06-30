#include "MacUtils.h"

MacUtils::MacUtils()
{
}

bool MacUtils::isInResizeArea(const QPointF& p, const QSizeF& size)
{
    constexpr qreal border = WindowConstants::ResizeBorder;
    constexpr qreal corner = border * 4.0;

    const qreal x = p.x();
    const qreal y = p.y();

    const qreal w = size.width();
    const qreal h = size.height();

    if (x <= corner && y <= corner &&
        (x > border || y > border))
    {
        return true;
    }

    if (x >= w - corner && y <= corner &&
        (x < w - border || y > border))
    {
        return true;
    }

    if (x <= corner && y >= h - corner &&
        (x > border || y < h - border))
    {
        return true;
    }

    if (x >= w - corner && y >= h - corner &&
        (x < w - border || y < h - border))
    {
        return true;
    }

    if (x <= border)
        return true;

    if (x >= w - border)
        return true;

    if (y <= border)
        return true;

    if (y >= h - border)
        return true;

    return false;
}