#include "pch.h"
#include "framework.h"
#include "module1.h"

int cchMax;
LPSTR buffer; //LPCSTR
UINT result;

//Callback-function
static BOOL CALLBACK MyWork_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM,HDC hdc)
{
    switch (iMessage)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            result = GetDlgItemTextA(hDlg, IDC_EDIT1, buffer, 255);

            TextOut(hdc, TA_CENTER, TA_CENTER, (LPSTR)result, 255);

            break;
        }
        if (LOWORD(wParam) == IDCANCEL)
            EndDialog(hDlg, 0);
        break;
    default: break;
    }
    return FALSE;
}
