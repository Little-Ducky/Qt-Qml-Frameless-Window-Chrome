#ifndef LINUXUTILS_H
#define LINUXUTILS_H

#include "domain/WindowConstants.h"

#include <QObject>
#include <QPointF>
#include <QSizeF>

class LinuxUtils
{
public:
    LinuxUtils();

    static Qt::Edges resizeEdges(const QPointF &pos, const QSizeF& size);
};

#endif // LINUXUTILS_H
