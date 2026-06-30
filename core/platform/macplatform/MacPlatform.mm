#include "MacPlatform.h"

#include <AppKit/AppKit.h>

MacPlatform::MacPlatform(QWindow *parent)
    : Platform(parent)
{
}

bool MacPlatform::nativeEvent(const QByteArray &type,
                                void *message,
                                qintptr *result)
{
    if (MacUtils::isInResizeArea(mapFromGlobal(QCursor::pos()), size()))
    {
        return false;
    }

    NSEvent* event = static_cast<NSEvent*>(message);

    NSView *view =
        (__bridge NSView *)(reinterpret_cast<void *>(winId()));

    NSWindow *window = view.window;

    if ([event type] == NSEventTypeLeftMouseDown)
    {
        NSButton *closeButton =
            [window standardWindowButton:NSWindowCloseButton];

        NSButton *miniButton =
            [window standardWindowButton:NSWindowMiniaturizeButton];

        NSButton *zoomButton =
            [window standardWindowButton:NSWindowZoomButton];

        NSPoint p = [event locationInWindow];

        NSView *titleBarView = closeButton.superview;

        NSPoint localPoint =
            [titleBarView convertPoint:p fromView:nil];

        bool overTrafficLights =
            NSPointInRect(localPoint, closeButton.frame) ||
            NSPointInRect(localPoint, miniButton.frame) ||
            NSPointInRect(localPoint, zoomButton.frame);

        if ([event clickCount] == 2)
        {
            NSString *action =
                [[NSUserDefaults standardUserDefaults]
                    stringForKey:@"AppleActionOnDoubleClick"];

            if ([action isEqualToString:@"Minimize"])
            {
                [window miniaturize:nil];
            }
            else if ([action isEqualToString:@"Maximize"] ||
                     [action isEqualToString:@"Zoom"] ||
                     [action isEqualToString:@"Fill"])
            {
                [window zoom:nil];
            }

            return true;
        }

        if (!overTrafficLights &&
            mapFromGlobal(QCursor::pos()).y() < m_captionController->height() &&
            !m_captionController->findInteractiveAt(contentItem(),
                                             mapFromGlobal(QCursor::pos())))
        {
            [window performWindowDragWithEvent:event];

            return true;
        }
    }

    return QQuickWindow::nativeEvent(type, message, result);
}

void MacPlatform::setup()
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

    [[NSNotificationCenter defaultCenter]

        addObserverForName:NSWindowWillStartLiveResizeNotification

                    object:window

                     queue:[NSOperationQueue mainQueue]

                usingBlock:^(NSNotification *note)

                           {
                                window.ignoresMouseEvents = YES;
                           }];

    [[NSNotificationCenter defaultCenter]

        addObserverForName:NSWindowDidEndLiveResizeNotification

                    object:window

                     queue:[NSOperationQueue mainQueue]

                usingBlock:^(NSNotification *note)

                           {
                              window.ignoresMouseEvents = NO;
                           }];
}