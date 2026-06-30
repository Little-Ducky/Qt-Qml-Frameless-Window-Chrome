#ifndef WINDOWSPLATFORM_H
#define WINDOWSPLATFORM_H

#include "platform/IPlatform.h"
#include "platform/BaseWindow.h"

#include <QObject>
#include <QQuickWindow>

class WindowsPlatform : public BaseWindow,
                               IPlatform
{
    Q_OBJECT

    QML_NAMED_ELEMENT(AppMainWindow)

public:
    explicit WindowsPlatform(QWindow *parent = nullptr);

    Q_INVOKABLE void setup() override;

protected:
    bool nativeEvent(const QByteArray &eventType,
                     void *message,
                     qintptr *result) override;

};

#endif // WINDOWSPLATFORM_H
