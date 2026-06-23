#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <Windowsx.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

#include <QtCore>

#include "platform/ui/appmainwindow/AppMainWindow.h"

// Shows and handles the Windows system menu manually.
// This is required for frameless/custom windows where the default title bar is removed.
// It restores standard system behavior (minimize, maximize, restore, move, size)
void showSysMenu(POINT pt, HWND hwnd)
{
    HMENU menu = GetSystemMenu(hwnd, FALSE);

    BOOL maximized = IsZoomed(hwnd);
    BOOL minimized = IsIconic(hwnd);

    EnableMenuItem(
        menu,
        SC_RESTORE,
        MF_BYCOMMAND |
            ((maximized || minimized)
                 ? MF_ENABLED
                 : MF_GRAYED));

    EnableMenuItem(
        menu,
        SC_MAXIMIZE,
        MF_BYCOMMAND |
            (maximized
                 ? MF_GRAYED
                 : MF_ENABLED));

    EnableMenuItem(
        menu,
        SC_MINIMIZE,
        MF_BYCOMMAND |
            (minimized
                 ? MF_GRAYED
                 : MF_ENABLED));

    EnableMenuItem(
        menu,
        SC_SIZE,
        MF_BYCOMMAND |
            (maximized
                 ? MF_GRAYED
                 : MF_ENABLED));

    EnableMenuItem(
        menu,
        SC_MOVE,
        MF_BYCOMMAND |
            (!maximized && !minimized ? MF_ENABLED : MF_GRAYED));

    UINT cmd = TrackPopupMenu(
        menu,
        TPM_RETURNCMD | TPM_RIGHTBUTTON,
        pt.x,
        pt.y,
        0,
        hwnd,
        nullptr);

    if (cmd)
    {
        PostMessage(
            hwnd,
            WM_SYSCOMMAND,
            cmd,
            0);
    }

}
// Calculates which resize border (if any) the mouse is currently hovering over.
// Used to emulate native window resizing behavior in a frameless window.
qintptr getResizeHitTest(RECT rect, LONG x, LONG y)
{
    const bool left =
        x >= rect.left &&
        x < rect.left + AppMainWindow::RESIZE_BORDER;

    const bool right =
        x < rect.right &&
        x >= rect.right - AppMainWindow::RESIZE_BORDER;

    const bool top =
        y >= rect.top &&
        y < rect.top + AppMainWindow::RESIZE_BORDER;

    const bool bottom =
        y < rect.bottom &&
        y >= rect.bottom - AppMainWindow::RESIZE_BORDER;

    if (top && left)
        return HTTOPLEFT;

    if (top && right)
        return HTTOPRIGHT;

    if (bottom && left)
        return HTBOTTOMLEFT;

    if (bottom && right)
        return HTBOTTOMRIGHT;

    if (left)
        return HTLEFT;

    if (right)
        return HTRIGHT;

    if (top)
        return HTTOP;

    if (bottom)
        return HTBOTTOM;

    return 0;
}

#endif // UTILS_H
