#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include <QObject>
#include <QQuickWindow>

class WindowController : public QObject
{
    Q_OBJECT

public:
    explicit WindowController(QObject *parent = nullptr);

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

#endif // WINDOWCONTROLLER_H