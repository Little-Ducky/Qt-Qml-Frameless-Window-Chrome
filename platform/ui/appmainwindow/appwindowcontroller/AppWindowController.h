#ifndef APPWINDOWCONTROLLER_H
#define APPWINDOWCONTROLLER_H

#include <QObject>
#include <QQuickWindow>

class AppWindowController : public QObject
{
    Q_OBJECT

public:
    explicit AppWindowController(QObject *parent = nullptr);

    Q_INVOKABLE void showFullScreen();
    Q_INVOKABLE void toggleMaximized();
    Q_INVOKABLE void showMinimized();
    Q_INVOKABLE void showMaximized();
    Q_INVOKABLE void showNormal();
    Q_INVOKABLE void close();

private:
    QQuickWindow* m_window = nullptr;

    int m_prevState = 0;
};

#endif // APPWINDOWCONTROLLER_H