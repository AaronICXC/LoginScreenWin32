#include <iostream>
#include <windows.h>

#define FILE_CLICK 0
#define SAVE_LOGIN 1
#define EXIT_PROGRAM 2
#define SUBMIT_BUTTON 3

// procedure
LRESULT CALLBACK wmProcedure(HWND, UINT, WPARAM, LPARAM);

void addMenus(HWND);

HWND hParent, hUser, hPass, hSubmit;

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
    int closeMsg;
    WCHAR uContent[28];
    WCHAR pContent[28];

    WCHAR uSaved[28];
    WCHAR pSaved[28];

    switch (msg) {
        case WM_COMMAND:
            switch(wp) {
                case BN_CLICKED:
                    GetWindowTextW(hUser, uContent, sizeof(uContent));
                    GetWindowTextW(hPass, pContent, sizeof(pContent));
                    if (uContent == uSaved && pContent == pSaved) {
                        MessageBoxW(hWnd, L"Login Successful!", L"Notification", MB_OK);
                    } else if (uContent == uSaved && pContent != pSaved) {
                        MessageBoxW(hWnd, L"Password Incorrect.", L"Notification", MB_OK);
                    } else if (uContent != uSaved && pContent == pSaved) {
                        MessageBoxW(hWnd, L"Username Incorrect.", L"Notification", MB_OK);
                    } else {
                        MessageBoxW(hWnd, L"Both fields are incorrect.", L"Notification", MB_OK);
                    }
                    break;
                case SAVE_LOGIN:
                    if (hUser || hPass) {
                        GetWindowTextW(hUser, uContent, sizeof(uContent));
                        GetWindowTextW(hPass, pContent, sizeof(pContent));

                        for (int i = 0; i < sizeof(uContent); i++) {
                            uSaved[i] = uContent[i];
                        }
                        for (int i = 0; i < sizeof(pContent); i++) {
                            pSaved[i] = pContent[i];
                        }

                        MessageBoxW(hWnd, L"Login Saved", L"Notification", MB_OK);
                    } else {
                        MessageBoxW(hWnd, L"Fields must not be blank.", L"Notification", MB_OK);
                    }
                    break;
                case EXIT_PROGRAM:
                    closeMsg = MessageBoxW(hWnd, L"Are you sure you want to exit?", L"Notification", MB_YESNO);
                    switch(closeMsg) {
                        case IDYES:
                            DestroyWindow(hWnd);
                            break;
                        case IDNO:
                            break;
                    }
                    break;
            }
            break;
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
    
    AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");

    // scope for file options
    {
        AppendMenuW(hFileMenu, MF_STRING, SAVE_LOGIN, L"Save Login");
        AppendMenuW(hFileMenu, MF_SEPARATOR, NULL, NULL);
        AppendMenuW(hFileMenu, MF_STRING, EXIT_PROGRAM, L"Exit");
    }

    hUser = CreateWindowW(L"Edit", L"Username", WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | ES_MULTILINE | WS_BORDER, 175, 100, 150, 20, hWnd, NULL, NULL, NULL);
    hPass = CreateWindowW(L"Edit", L"Password", WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | ES_MULTILINE | WS_BORDER, 175, 130, 150, 20, hWnd, NULL, NULL, NULL);

    hSubmit = CreateWindowW(L"Button", L"Submit", WS_VISIBLE | WS_CHILD | WS_BORDER, 210, 170, 75, 20, hWnd, NULL, NULL, NULL);


    SetMenu(hWnd, hMenu);
}