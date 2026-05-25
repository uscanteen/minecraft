#include <windows.h>
#include "vgui.h"

// Declare the window proc from your renderer file
extern LRESULT CALLBACK vgui_window_proc(HWND, UINT, WPARAM, LPARAM);

// If pPlayer is a global in your renderer, declare it here too
extern Player* pPlayer;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmd, int nShow) {
    // 1. Register window class
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = vgui_window_proc;  // your renderer's proc
    wc.hInstance     = hInstance;
    wc.lpszClassName = "VGUIWindow";
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    // 2. Create the window
    HWND hwnd = CreateWindow(
        "VGUIWindow", "3D Renderer",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nShow);
    UpdateWindow(hwnd);

    // 3. Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // Trigger a redraw every frame for animation
        InvalidateRect(hwnd, NULL, FALSE);
    }

    return (int)msg.wParam;
}