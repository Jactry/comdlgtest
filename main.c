#include <windows.h>
#include <commctrl.h>
#include "main_res.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HRESULT WINAPI MyDialog(HWND hwnd);

int iCurrentColor  = IDC_BLACK,
    iCurrentFigure = IDC_RECT;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE hInstance;
    PAINTSTRUCT ps;
    HWND hwndButton;

    switch (message)
        {
        case WM_CREATE:
            hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
            hwndButton = CreateWindowA("BUTTON", "OK",
                                       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
                                       10, 10, 80, 40, hwnd, (HMENU)IDC_MAIN_BUTTON,
                                       (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
                                       NULL);
            return 0;

        case WM_COMMAND:
            switch (LOWORD(wParam))
                {
                case IDC_MAIN_BUTTON:
                    MyDialog(hwnd);
                    /* ShellAboutA(hwnd, "Demo Program", "Wine", NULL); */
                    return 0;
                }
            break;

        case WM_PAINT:
            BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);

            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("Demo");
    MSG msg;
    HWND hwnd;
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(hInstance, szAppName);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszClassName = szAppName;
     
    if (!RegisterClass(&wndclass))
        {
            MessageBox(NULL, TEXT("This program requires Windows NT!"),
                       szAppName, MB_ICONERROR);
            return 0;
        }

    hwnd = CreateWindow(szAppName, TEXT ("Demo Program"),
                        WS_OVERLAPPEDWINDOW, 0, 0, 100, 90,
                        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd); 
     
    while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    return msg.wParam;
}
