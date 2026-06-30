#ifndef APPCAPTION_H
#define APPCAPTION_H

#include <QObject>
#include <QGuiApplication>
#include <QQuickWindow>
#include <QQuickItem>

class CaptionController : public QObject
{
    Q_OBJECT

public:
    explicit CaptionController(QObject *parent = nullptr);

    inline static constexpr int HEIGHT_CAPTION_BASE = 40;

    bool isIgnorable(QQuickItem *i);
    bool isInteractive(QQuickItem *i);
    QQuickItem* findInteractiveAt(QQuickItem *parent, const QPointF &scenePos);

    Q_INVOKABLE int height() const;
};

#endif // APPCAPTION_H