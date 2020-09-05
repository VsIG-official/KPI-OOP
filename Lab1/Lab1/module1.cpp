#include "pch.h"
#include "framework.h"
#include "module1.h"

int const maxSymbols = 255;
TCHAR tempPlaceForText[maxSymbols] = { 0 };

int pos;
int nMinPos = 1;
int nMaxPos = 100;
HWND hWndScrollBar;

//Callback-function
INT_PTR CALLBACK Work1_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_INITDIALOG:
        hWndScrollBar = GetDlgItem(hDlg, IDC_SCROLLBAR1);
        SetScrollRange(hWndScrollBar, SB_CTL, nMinPos, nMaxPos, TRUE);
        break;
    case WM_HSCROLL:
        pos = GetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL);
        switch (LOWORD(wParam))
        {
        case SB_LINELEFT:
            pos--;
            SetDlgItemInt(hDlg, IDC_STATIC_MOD1, pos, TRUE);
            break;
        case SB_LINERIGHT:
            pos++;
            SetDlgItemInt(hDlg, IDC_STATIC_MOD1, pos, TRUE);
            break;
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            pos = HIWORD(wParam);
            SetDlgItemInt(hDlg, IDC_STATIC_MOD1, pos, TRUE);
            break;
        default: break;
        }
        SetScrollPos(hWndScrollBar, SB_CTL, pos, TRUE);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    default: break;
    }
    return FALSE;
}
