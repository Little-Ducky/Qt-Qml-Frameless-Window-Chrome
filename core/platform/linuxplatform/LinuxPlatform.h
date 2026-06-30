#ifndef LINUXPLATFORM_H
#define LINUXPLATFORM_H

#include "platform/IPlatform.h"
#include "platform/BaseWindow.h"

#include "utils/LinuxUtils.h"

class LinuxPlatform : public BaseWindow,
                             IPlatform
{
    Q_OBJECT

    QML_NAMED_ELEMENT(AppMainWindow)

public:
    explicit LinuxPlatform(QWindow *parent = nullptr);

    Q_INVOKABLE void setup() override;

protected:
    bool nativeEvent(const QByteArray &eventType,
                     void *message,
                     qintptr *result) override;

    bool event(QEvent *e) override;
};


#endif // LINUXPLATFORM_H