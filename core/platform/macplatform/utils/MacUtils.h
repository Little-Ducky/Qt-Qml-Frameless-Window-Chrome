#ifndef MACUTILS_H
#define MACUTILS_H

#include <QObject>
#include <QPointF>
#include <QSize>

#include "domain/WindowConstants.h"

class MacUtils
{
public:
    MacUtils();

    static bool isInResizeArea(const QPointF& p, const QSizeF& size);
};

#endif // MACUTILS_H
