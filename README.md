# Qt-Frameless-Window-Chrome

Custom Frameless Window component for Qt Quick (QML).
Provides full control over the title bar, window resizing, system menu, and native window behavior.

Windows and Mac implementations are included, while Linux currently rely on native system window decorations.

---

## Overview

This project provides a native-like window experience for Qt Quick applications with a fully custom window chrome implementation on Windows, MacOS.

It is designed as a modular and extensible solution for building custom title bars and frameless windows.

---

## Demo (Windows 11)

Example of how the custom window behaves on Windows 11, including native-like window movement, resizing, and system menu integration.

<img width="800" height="449" alt="ezgif-17418d93a23a6e5e" src="https://github.com/user-attachments/assets/06abeae9-cc5e-4ab1-a10f-f7ca68c3c153" />

## Screen MacOs

<img width="1480" height="1086" alt="obrazek" src="https://github.com/user-attachments/assets/2cc882f5-c06f-4384-8066-0d1c520d1400" />

## Features windows

- Frameless window support ✔️
- Custom title bar implementation ✔️
- Window resizing (native-like border behavior) ✔️
- Window moving via custom caption area ✔️
- System menu integration (Alt + Space, right-click menu) ✔️
- Windows Aero / DWM integration ✔️
- Full control over non-client area on Windows ✔️

## Features macOS

- Frameless window support ✔️
- Custom title bar implementation ✔️
- Native window resizing ✔️
- Window moving via custom caption area ✔️
- Native traffic light button support ✔️
- Native double-click title bar action (Minimize / Zoom) ✔️
- Full-size content view integration ✔️

## Platform Support

| Platform | Support status | Notes |
|----------|---------------|------|
| Windows  | ✔ Fully supported | Custom window chrome implementation (WinAPI + Qt) |
| macOS    | ✔ Fully supported | Custom window chrome implementation (Cocoa (AppKit) + Qt) |
| Linux    | ✖ Not implemented | Uses native system window decorations |

---

## Windows 11 Notes

Due to full custom non-client area implementation (WM_NCCALCSIZE / WM_NCHITTEST), some native Windows 11 features are not available:

- Snap Layouts on maximize button hover ❌

---

## Architecture Notes

- Linux currently rely on system window managers
- Architecture is designed to be extensible for future platform-specific backends
- Controller-based window management API exposed to QML

---

## Notes

This project focuses on providing full control over window chrome behavior while maintaining clean separation between platform-specific implementations.
