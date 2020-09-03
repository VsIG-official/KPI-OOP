#include "pch.h"
#include "framework.h"
#include "module1.h"

int cchMax;
TCHAR buffer[255] = { 0 };

//Callback-function
 INT_PTR CALLBACK MyWork_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            GetDlgItemText(hDlg, IDC_EDIT1, buffer, 255);
            EndDialog(hDlg, 0);
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL) EndDialog(hDlg, 0);
        return (INT_PTR)TRUE;
    default: break;
    }
    return (INT_PTR)FALSE;
}
