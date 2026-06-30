#include "WindowsPlatform.h"

#include <windows.h>
#include <Windowsx.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

#include "utils/WindowsUtils.h"

WindowsPlatform::WindowsPlatform(QWindow *parent)
    : BaseWindow(parent)
{}

void WindowsPlatform::setup()
{
    DWM_WINDOW_CORNER_PREFERENCE pref = DWMWCP_ROUND;

    // Sets the window corner style (rounded / squared) using Windows DWM.
    // This controls how the window borders are rendered in modern Windows (11+),
    // allowing custom UI windows to match the system visual style.
    HRESULT hr = DwmSetWindowAttribute(
        HWND(winId()),
        DWMWA_WINDOW_CORNER_PREFERENCE,
        &pref,
        sizeof(pref)
        );

    if (FAILED(hr)) {
        qWarning() << "DWM attribute failed:" << hr;
    }

    QRect screenGeometry = screen()->availableGeometry();

    int x = screenGeometry.x() +
            (screenGeometry.width() - width()) / 2;

    int y = screenGeometry.y() +
            (screenGeometry.height() - height()) / 2;

    setPosition(x, y);
}

// This function handles native Windows events to emulate custom title bar behavior
// and override default window behavior (minimize, restore, etc.) for a custom UI.
// It is used to simulate and control standard window actions manually when using
bool WindowsPlatform::nativeEvent(const QByteArray& eventType,
                            void *message,
                            qintptr *result)
{
    MSG *msg = static_cast<MSG*>(message);

    switch (msg->message)
    {
    case WM_SYSCOMMAND:
    {
        switch (msg->wParam & 0xFFF0)
        {
        case SC_MINIMIZE:
            // Window is being minimized via system command (title bar, taskbar, Win key, etc.)
            m_windowController->showMinimized();
            return true;

        case SC_RESTORE:
            // Window is being restored from minimized/maximized state
            m_windowController->showNormal();
            return true;

        default:
            break;
        }

        break;
    }
    case WM_NCCALCSIZE:
    {
        if (msg->wParam)
        {
            // Fixes maximized window sizing by setting the client area to the monitor's work area.
            // This removes unwanted borders, gaps, and incorrect padding when the window is maximized.
            if (IsZoomed(msg->hwnd))
            {
                NCCALCSIZE_PARAMS* params =
                    reinterpret_cast<NCCALCSIZE_PARAMS*>(msg->lParam);

                MONITORINFO mi{};
                mi.cbSize = sizeof(mi);

                GetMonitorInfo(
                    MonitorFromWindow(msg->hwnd, MONITOR_DEFAULTTONEAREST),
                    &mi);

                params->rgrc[0] = mi.rcWork;
            }
        }

        // This is used to remove the default Windows non-client area (title bar, borders, shadows).
        // By returning 0 and manually setting the client rect, we fully take control of window sizing.
        *result = 0;
        return true;
    }
    case WM_SYSKEYDOWN:
    {
        // Simulates the standard Windows system menu shortcut (Alt + Space)
        // because the default non-client behavior is overridden in a custom window.
        // This ensures the system menu still works even with a custom title bar.
        if (msg->wParam == VK_SPACE &&
            (GetKeyState(VK_MENU) & 0x8000))
        {
            POINT pt;
            pt.x = 0;
            pt.y = 0;

            ClientToScreen(msg->hwnd, &pt);

            WindowsUtils::showSysMenu(pt, msg->hwnd);

            return true;
        }

        break;
    }
    case WM_NCRBUTTONUP:
    {
        // Simulates the standard Windows behavior of opening the system menu
        // when right-clicking the window caption (title bar area).
        // This is required because the native title bar is replaced.
        if (msg->wParam == HTCAPTION)
        {
            POINT pt;
            GetCursorPos(&pt);

            WindowsUtils::showSysMenu(pt, msg->hwnd);

            return true;
        }

        break;
    }
    case WM_NCHITTEST:
    {
        // Handles hit-testing for a frameless/custom window.
        // This replaces the default Windows behavior for borders, resize areas, and title bar interaction.

        RECT rect;
        GetWindowRect(msg->hwnd, &rect);

        const LONG x = GET_X_LPARAM(msg->lParam);
        const LONG y = GET_Y_LPARAM(msg->lParam);

        qintptr resizeSide = WindowsUtils::getResizeHitTest(rect, x, y);

        if (resizeSide)
        {
            // If the cursor is on a resize edge, return the corresponding resize handle
            // so Windows can perform resizing even without a native window frame.
            *result = resizeSide;

            return true;
        }

        POINT pt;
        pt.x = x;
        pt.y = y;
        // Translates mouse position so the window knows where the cursor is inside it
        // (needed for dragging to work correctly).
        ScreenToClient(msg->hwnd, &pt);

        // Checks if the cursor is inside the custom caption (title bar area)
        // and ensures it's not over an interactive UI element (buttons, inputs, etc.)
        if (pt.y < m_captionController->height() &&
            !m_captionController->findInteractiveAt(contentItem(), mapFromGlobal(QCursor::pos())))
        {
            *result = HTCAPTION;
            return true;
        }
        // Default client area (interactive content inside the window)
        *result = HTCLIENT;
        return true;
    }
    }

    return QQuickWindow::nativeEvent(eventType, message, result);
}