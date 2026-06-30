#ifndef WINDOWSUTILS_H
#define WINDOWSUTILS_H

#include <windows.h>
#include <Windowsx.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

#include <QtCore>

#include "domain/WindowConstants.h"

class WindowsUtils
{
public:
    WindowsUtils();

    static void showSysMenu(POINT pt, HWND hwnd);
    static qintptr getResizeHitTest(RECT rect, LONG x, LONG y);
};

#endif // WINDOWSUTILS_H
