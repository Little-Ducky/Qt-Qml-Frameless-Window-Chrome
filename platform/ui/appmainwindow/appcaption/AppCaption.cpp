#include "AppCaption.h"

AppCaption::AppCaption(QObject *parent)
    : QObject{parent}
{
}

// Returns the effective caption height in device pixels.
// The value is scaled according to the screen's devicePixelRatio
// to ensure correct sizing on high-DPI displays.
int AppCaption::height() const
{
    return qRound(HEIGHT_CAPTION_BASE * qobject_cast<QWindow*>(parent())->screen()->devicePixelRatio());
}

// Determines whether a QML item should be ignored during hit-testing.
// Typically ignores static text elements that should not block window dragging.
bool AppCaption::isIgnorable(QQuickItem *i)
{
    if (!i)
        return true;

    if (i->inherits("QQuickLabel") ||
        i->inherits("QQuickText"))
        return true;

    return false;
}

// Checks whether a QML item is interactive (can receive mouse input).
// Used to prevent treating clickable UI elements as draggable caption area.
bool AppCaption::isInteractive(QQuickItem *i)
{
    if (!i)
        return false;

    return i->acceptedMouseButtons() != Qt::NoButton;
}

// Recursively searches for an interactive QML item under the given scene position.
// Used to determine whether the mouse is over a clickable element inside the caption area,
// so that dragging the window is disabled in that case.
QQuickItem* AppCaption::findInteractiveAt(QQuickItem *parent,
                                             const QPointF &scenePos)
{
    if (!parent || !parent->isVisible())
        return nullptr;

    const auto children = parent->childItems();

    // Iterate from topmost (front) item to bottommost (back)
    for (auto it = children.rbegin(); it != children.rend(); ++it)
    {
        QQuickItem *child = *it;

        if (!child || !child->isVisible())
            continue;

        QPointF p = child->mapFromScene(scenePos);

        // Skip items that are not under cursor or should be ignored
        if (!child->contains(p) || isIgnorable(child))
            continue;

        // If the item is interactive, stop search and return it
        if (isInteractive(child))
            return child;

        // Otherwise search deeper in the item hierarchy
        QQuickItem *deep = findInteractiveAt(child, scenePos);
        if (deep)
            return deep;
    }

    return nullptr;
}