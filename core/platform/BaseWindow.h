#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QQuickWindow>

#include "captioncontroller/captionController.h"
#include "windowcontroller/windowController.h"

class BaseWindow : public QQuickWindow
{
    Q_OBJECT
    QML_ANONYMOUS

    Q_PROPERTY(CaptionController* captionController READ captionController CONSTANT FINAL)
    Q_PROPERTY(WindowController* windowController READ windowController CONSTANT FINAL)

public:
    explicit BaseWindow(QWindow *parent = nullptr);
    ~BaseWindow() override = default;

    CaptionController* captionController() const;
    WindowController* windowController() const;

protected:
    CaptionController* m_captionController = nullptr;
    WindowController* m_windowController = nullptr;
};

#endif // BASEWINDOW_H