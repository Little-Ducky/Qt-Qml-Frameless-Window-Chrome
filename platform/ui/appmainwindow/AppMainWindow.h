#ifndef APPMAINWINDOW_H
#define APPMAINWINDOW_H

#include <QtQml>
#include <QQuickWindow>
#include <QQuickItem>
#include <QCursor>

#include "appcaption/AppCaption.h"
#include "appwindowcontroller/AppWindowController.h"

class AppMainWindow : public QQuickWindow
{
    Q_OBJECT

    Q_PROPERTY(int RESIZE_BORDER MEMBER RESIZE_BORDER CONSTANT)
    Q_PROPERTY(AppWindowController* controller MEMBER m_appWindowController CONSTANT)

    Q_PROPERTY(AppCaption* caption READ caption CONSTANT)

public:
    explicit AppMainWindow(QWindow *parent = nullptr);

    inline static constexpr int RESIZE_BORDER = 4;

    AppCaption* caption() const
    {
        return m_appCaption;
    }

    Q_INVOKABLE void setup();

protected:
    bool nativeEvent(const QByteArray &eventType,
                     void *message,
                     qintptr *result) override;

private:
    AppCaption* m_appCaption = nullptr;
    AppWindowController* m_appWindowController = nullptr;
};

#endif // APPMAINWINDOW_H
