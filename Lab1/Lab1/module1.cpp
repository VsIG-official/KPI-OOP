#include "pch.h"
#include "framework.h"
#include "resource1.h"

int sss;
LPTSTR buferrr;

//Callback-функція вікна
static BOOL CALLBACK MyWork(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM)
{
    switch (iMessage)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            //... можливо, щось ще
            //зчитуємо вміст елементу Edit Control у буфер
            GetDlgItemText(hDlg, IDC_EDIT1, buferrr, sss);
            //... можливо, щось ще
            EndDialog(hDlg, 1);
            break;
        }
        if (LOWORD(wParam) == IDCANCEL) EndDialog(hDlg, 0);
        break;
    default: break;
    }
    return FALSE;
}