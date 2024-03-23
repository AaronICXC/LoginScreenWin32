#include <iostream>
#include <windows.h>

#define FILE_CLICK 0

// procedure
LRESULT CALLBACK wmProcedure(HWND, UINT, WPARAM, LPARAM);

void addMenus(HWND);

HWND hParent;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE prevInst, LPSTR args, int ncmdshow) {
    ncmdshow = 0;

    WNDCLASSW wm = {0};

    {
        wm.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wm.hCursor = LoadCursor(NULL, IDC_ARROW);
        wm.hInstance = hInst;
        wm.lpszClassName = L"loginProject";
        wm.lpfnWndProc = wmProcedure;
    }

    if (!(RegisterClassW(&wm)))
        return -1;

    hParent = CreateWindowW(L"loginProject", L"Login", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 500, 500, NULL, NULL, NULL, NULL);

    MSG msg = {0};

    while (GetMessage(&msg, NULL, NULL, NULL)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK wmProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            addMenus(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
            break;
    }
}

void addMenus(HWND hWnd) {
    HMENU hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    AppendMenuW(hMenu, MF_STRING, FILE_CLICK, L"File");


    SetMenu(hWnd, hMenu);
}