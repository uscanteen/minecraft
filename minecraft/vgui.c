#include <stdlib.h>
#include "vgui.h"
#include <windows.h>
#include <stdio.h>
void plyRot(Vertex3D vert, int* out_screen_x, int* out_screen_y);
void DrawBlock3D(float world_x, float world_y, float world_z, HDC hdc);
static Player g_player = {0.0f, 0.0f, 5.0f, 1.0f}
Player* player = &g_player;

#define MAX_PANELS 128
static VGUIPANEL* g_panels[MAX_PANELS];
static int g_panel_count = 0;

static LRESULT CALLBACK vgui_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        // Paint the screen
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            DrawBlock3D(0.0f, 0.0f, 0.0f, hdc);
            HBRUSH brush = CreateSolidBrush(RGB(56, 59, 51));

            for (int i = 0; i < g_panel_count; i++) {
                VGUIPANEL* p = g_panels[i];
                RECT rect = { p->x, p->y, p->x + p->width, p->y + p->height };
                FillRect(hdc, &rect, brush);
            }

            DeleteObject(brush);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


void plyRot(Vertex3D vert, int* out_screen_x, int* out_screen_y) {
    float x_rot = vert.x - pPlayer->x;
    float y_rot = vert.y - pPlayer->y;
    float z_rot = vert.z - pPlayer->z;

    if (z_rot <= 0.1f) {
        z_rot = 0.1f;
    }

    *out_screen_x = (int)((x_rot * 200.0f) / z_rot) + 400;
    *out_screen_y = (int)((y_rot * 200.0f) / z_rot) + 300;
}

// Finally, draw 3D blocks.
void DrawBlock3D(float world_x, float world_y, float world_z, HDC hdc) {
    if (pPlayer == NULL) return;

    Vertex3D test_points[4] = {
        { -1.0f, -1.0f,  2.0f },
        {  1.0f, -1.0f,  2.0f },
        {  1.0f,  1.0f,  2.0f },
        { -1.0f,  1.0f,  2.0f }
    };

    Edge3D test_edges[4] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}
    };

    HPEN white_pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
    HPEN old_pen = (HPEN)SelectObject(hdc, white_pen);

    for (int i = 0; i < 4; i++) {
        Vertex3D p1 = test_points[test_edges[i].start];
        Vertex3D p2 = test_points[test_edges[i].end];

        int p1_x, p1_y;
        int p2_x, p2_y;

        plyRot(p1, &p1_x, &p1_y);
        plyRot(p2, &p2_x, &p2_y);

        MoveToEx(hdc, p1_x, p1_y, NULL);
        LineTo(hdc, p2_x, p2_y);
    }

    SelectObject(hdc, old_pen);
    DeleteObject(white_pen);
}

int vgui_initialize(const char* title, int width, int height) {
    HINSTANCE hInst = GetModuleHandle(NULL);
    WNDCLASS wc = {0};

    wc.lpfnWndProc = vgui_window_proc;
    wc.hInstance = hInst;
    wc.lpszClassName = "VGUI_WindowClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, "VGUI_WindowClass", title, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, NULL, hInst, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 1;
}

void pPlayer_mov(float move_x, float move_y, float move_z) {
    if (pPlayer != NULL) {
        pPlayer->x += move_x * player->move_speed;
        pPlayer->y += move_y * player->move_speed;
        pPlayer->z += move_z * player->move_speed;
    }
}

VGUIPANEL* vgui_create_panel(const char* type) {
    VGUIPANEL* panel = (VGUIPANEL*)malloc(sizeof(VGUIPANEL));
    
    if (panel == NULL) {
        printf("FATAL ERROR CREATING GUI: ERROR 10 : NOT ENOUGH RAM!\n");
        return NULL;
    }

    panel->type = type;
    panel->x = 0;
    panel->y = 0;
    panel->width = 100;
    panel->height = 100;

    if (g_panel_count < MAX_PANELS) {
        g_panels[g_panel_count] = panel;
        g_panel_count++;
        printf("VGUI: Successfully registered '%s' to roster spot %d\n", type, g_panel_count);
    }

    return panel;
}


const VGUISYS VGUI = {
    .Create = vgui_create_panel
};