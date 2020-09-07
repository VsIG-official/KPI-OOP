#include "pch.h"
#include "framework.h"
#include "module1.h"

#pragma region Variables

int const maxSymbols = 255;
char tempPlaceForText[maxSymbols] = { 0 };

int pos;
int nMinPos = 1;
int nMaxPos = 100;
HWND hWndScrollBar;
BOOL canWrite = FALSE;
int numOfDig;

#pragma endregion

#pragma region Funtions

/// <summary>
/// Callback-function for hor.scrollbar
/// </summary>
/// <param name="hDlg"></param>
/// <param name="iMessage"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
INT_PTR CALLBACK Work1_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_INITDIALOG:
        hWndScrollBar = GetDlgItem(hDlg, IDC_SCROLLBAR1);
        pos = 1;
        SetScrollRange(hWndScrollBar, SB_CTL, nMinPos, nMaxPos, TRUE);
        break;
    case WM_HSCROLL:
        pos = GetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL);
        switch (LOWORD(wParam))
        {
        case SB_LINELEFT:
            if (pos != nMinPos)
            {
                pos--;
            }
            SetDlgItemInt(hDlg, IDC_STATIC_MOD1, pos, TRUE);
            break;
        case SB_LINERIGHT:
            if (pos != nMaxPos)
            {
                pos++;
            }
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
        switch (LOWORD(wParam))
        {
        case IDOK:
            canWrite = TRUE;
            numOfDig = Count(pos);
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
        break;
    default: break;
    }
    return FALSE;
}

/// <summary>
/// Function to Count how many digits are in int
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
int Count(int pos)
{
    int count = 0;
    while (pos != 0)
    {
        pos = pos / 10;
        ++count;
    }
    return count;
}

#pragma endregion
