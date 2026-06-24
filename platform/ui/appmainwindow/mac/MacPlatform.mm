#include "../AppMainWindow.h"

#include <AppKit/AppKit.h>

// macOS implementation of AppMainWindow
// Currently uses the native macOS window title bar and window behavior (standard system chrome).
// In the future, this implementation may also be overridden to support a fully custom title bar,
// similar to the Windows frameless implementation.
AppMainWindow::AppMainWindow(QWindow *parent)
    : QQuickWindow(parent),
    m_appCaption(new AppCaption(this)),
    m_appWindowController(new AppWindowController(this))
{
}
enum ResizeEdge
{
    None = 0,

    Left,
    Right,

    Top,
    Bottom,

    TopLeft,
    TopRight,

    BottomLeft,
    BottomRight
};
// Native event handler is currently not customized on macOS.
// All system events are handled by the default QQuickWindow implementation.
bool AppMainWindow::nativeEvent(const QByteArray &type,
                                void *message,
                                qintptr *result)
{


    NSEvent* event = static_cast<NSEvent*>(message);

    if ([event type] == NSEventTypeLeftMouseDown)
    {

        NSView *view =
            (__bridge NSView *)(reinterpret_cast<void *>(winId()));

        NSWindow *window = view.window;


        NSButton *closeButton =
            [window standardWindowButton:NSWindowCloseButton];

        NSButton *miniButton =
            [window standardWindowButton:NSWindowMiniaturizeButton];

        NSButton *zoomButton =
            [window standardWindowButton:NSWindowZoomButton];

        NSPoint p = [event locationInWindow];

        constexpr int Border = 4;
        constexpr int Corner = Border * 2;

        bool topLeft =
            p.x <= Corner &&
            p.y <= Corner;

        bool topRight =
            p.x >= width() - Corner &&
            p.y <= Corner;

        bool bottomLeft =
            p.x <= Corner &&
            p.y >= height() - Corner;

        bool bottomRight =
            p.x >= width() - Corner &&
            p.y >= height() - Corner;

        bool left =
            p.x <= Border;

        bool right =
            p.x >= width() - Border;

        bool top =
            p.y <= Border;

        bool bottom =
            p.y >= height() - Border;

        int m_resizeEdge = None;

        if (topLeft)
        {
            m_resizeEdge = TopLeft;
        }
        else if (topRight)
        {
            m_resizeEdge = TopRight;
        }
        else if (bottomLeft)
        {
            m_resizeEdge = BottomLeft;
        }
        else if (bottomRight)
        {
            m_resizeEdge = BottomRight;
        }
        else if (left)
        {
            m_resizeEdge = Left;
        }
        else if (right)
        {
            m_resizeEdge = Right;
        }
        else if (top)
        {
            m_resizeEdge = Top;
        }
        else if (bottom)
        {
            m_resizeEdge = Bottom;
        }

        bool canResize =
            m_resizeEdge != None;

        if (canResize)
        {
            return false;
        }
        NSView *titleBarView = closeButton.superview;

        NSPoint localPoint =
            [titleBarView convertPoint:p fromView:nil];

        bool overTrafficLights =
            NSPointInRect(localPoint, closeButton.frame) ||
            NSPointInRect(localPoint, miniButton.frame) ||
            NSPointInRect(localPoint, zoomButton.frame);

        if ([event clickCount] == 2)
        {
            NSView *view =
                (__bridge NSView *)(reinterpret_cast<void *>(winId()));

            NSWindow *window = view.window;

            [window zoom:nil];

            return true;
        }

        if (!overTrafficLights &&
            mapFromGlobal(QCursor::pos()).y() < m_appCaption->height() &&
            !m_appCaption->findInteractiveAt(contentItem(),
                                             mapFromGlobal(QCursor::pos())))
        {
            [window performWindowDragWithEvent:event];

            return true;
        }
    }


    return QQuickWindow::nativeEvent(type, message, result);
}

// Placeholder for future macOS-specific initialization logic.
void AppMainWindow::setup()
{
    NSView *view =
        (__bridge NSView *)(reinterpret_cast<void *>(winId()));

    NSWindow *window = view.window;

    auto applyStyle = ^(NSWindow *w)
    {
        w.styleMask |= NSWindowStyleMaskTitled;
        w.styleMask |= NSWindowStyleMaskFullSizeContentView;

        w.titleVisibility = NSWindowTitleHidden;
        w.titlebarAppearsTransparent = YES;
    };

    applyStyle(window);

    [[NSNotificationCenter defaultCenter]
        addObserverForName:NSWindowDidEnterFullScreenNotification
                    object:window
                     queue:nil
                usingBlock:^(NSNotification *note)
                           {
                               applyStyle((NSWindow *)note.object);
                           }];

    [[NSNotificationCenter defaultCenter]
        addObserverForName:NSWindowDidExitFullScreenNotification
                    object:window
                     queue:nil
                usingBlock:^(NSNotification *note)
                           {
                               applyStyle((NSWindow *)note.object);
                           }];
}