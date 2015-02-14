#include <windows.h>
#include <stdio.h>
#include <dialog_res.h>
#include <commctrl.h>

static HINSTANCE instance;
int iCurrentColor  = IDC_BLACK,
    iCurrentFigure = IDC_RECT;

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message, 
                            WPARAM wParam, LPARAM lParam)
{
    static int  iColor, iFigure;
     
    switch (message)
        {
        case WM_INITDIALOG:
            iColor = iCurrentColor;
            iFigure = iCurrentFigure;
          
            CheckRadioButton(hDlg, IDC_BLACK, IDC_WHITE,   iColor);
            CheckRadioButton(hDlg, IDC_RECT,  IDC_ELLIPSE, iFigure);

            SetFocus(GetDlgItem (hDlg, iColor));
            return FALSE;

        case WM_COMMAND:
            switch (LOWORD(wParam))
                {
                case IDOK:
                    iCurrentColor = iColor;
                    iCurrentFigure = iFigure;
                    EndDialog(hDlg, TRUE);
                    return TRUE;
               
                case IDCANCEL:
                    EndDialog(hDlg, FALSE);
                    return TRUE;
               
                case IDC_BLACK:
                case IDC_RED:
                case IDC_GREEN:
                case IDC_YELLOW:
                case IDC_BLUE:
                case IDC_MAGENTA:
                case IDC_CYAN:
                case IDC_WHITE:
                    iColor = LOWORD(wParam);
                    CheckRadioButton(hDlg, IDC_BLACK, IDC_WHITE, LOWORD (wParam));
                    return TRUE;
               
                case IDC_RECT:
                case IDC_ELLIPSE:
                    iFigure = LOWORD(wParam);
                    CheckRadioButton(hDlg, IDC_RECT, IDC_ELLIPSE, LOWORD (wParam));
                    return TRUE;
                }
            break;
          
        case WM_PAINT:
            break;
        }
    return FALSE;
}

HRESULT WINAPI MyDialog(HWND hwnd)
{
    printf("MyDialog\n");
    InitCommonControls();
    DialogBox(instance, TEXT("AboutBox"), hwnd, AboutDlgProc);
    return S_OK;
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD reason, LPVOID reserved)
{
    HANDLE hActCtx;
    ACTCTXA actCtx;
    ULONG_PTR cookie;

    switch (reason)
        {
        case DLL_PROCESS_ATTACH:
            ZeroMemory(&actCtx, sizeof(actCtx));
            actCtx.cbSize = sizeof(actCtx);
            actCtx.hModule = GetModuleHandleA("comctl32.dll");
            actCtx.lpResourceName = MAKEINTRESOURCE(2);
            actCtx.dwFlags = ACTCTX_FLAG_HMODULE_VALID | ACTCTX_FLAG_RESOURCE_NAME_VALID;
            hActCtx = CreateActCtx(&actCtx);
            ActivateActCtx(hActCtx, &cookie);
            instance = hinst;
            DisableThreadLibraryCalls(hinst);
            printf("Hello attach\n");
            break;
        case DLL_PROCESS_DETACH:
            printf("Bye detach\n");
        }
    return TRUE;
}
