#include "pch.h"
#include "framework.h"
#include "module1.h"

int const maxSymbols = 255;
TCHAR buffer[maxSymbols] = { 0 };

//Callback-function
 INT_PTR CALLBACK Work1_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            // OK button
            GetDlgItemText(hDlg, IDC_EDIT1, buffer, maxSymbols);
            EndDialog(hDlg, 0);
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL)
        {
            // Cancel button
            EndDialog(hDlg, 0);
        }
        return (INT_PTR)TRUE;
    default: break;
    }
    return (INT_PTR)FALSE;
}
