#ifndef MACPLATFORM_H
#define MACPLATFORM_H

#include "platform/IPlatform.h"
#include "platform/BaseWindow.h"

#include "utils/MacUtils.h"

class MacPlatform : public BaseWindow,
                           IPlatform
{
    Q_OBJECT

    QML_NAMED_ELEMENT(AppMainWindow)

public:
    explicit MacPlatform(QWindow *parent = nullptr);

    Q_INVOKABLE void setup() override;

protected:
    bool nativeEvent(const QByteArray &eventType,
                     void *message,
                     qintptr *result) override;

private:
    MacUtils macUtils;
};

#endif // MACPLATFORM_H
