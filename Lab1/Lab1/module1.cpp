#include "pch.h"
#include "framework.h"
#include "module1.h"
#include "Lab1.h"

int cchMax;
LPSTR buffer; //LPCSTR
//UINT result;

//Callback-function
static BOOL CALLBACK MyWork_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM,HDC hdc)
{
    switch (iMessage)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {

            GetDlgItemText(hDlg, IDC_EDIT1, buffer, 255);
            //Draw(hDlg);
            break;
        }
        if (LOWORD(wParam) == IDCANCEL)
            EndDialog(hDlg, 0);
        break;
    default: break;
    }
    return FALSE;
}
