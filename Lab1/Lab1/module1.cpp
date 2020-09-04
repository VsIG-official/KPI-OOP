#include "pch.h"
#include "framework.h"
#include "module1.h"

int const maxSymbols = 255;
TCHAR tempPlaceForText[maxSymbols] = { 0 };

int pos;
int nMinPos = 1;
int nMaxPos = 100;

//Callback-function
INT_PTR CALLBACK Work1_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_INITDIALOG:
        SetScrollRange(hDlg, IDC_SCROLLBAR1,nMinPos,nMaxPos,TRUE);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            // OK button
            GetDlgItemText(hDlg, IDC_SCROLLBAR1, tempPlaceForText, maxSymbols);
            EndDialog(hDlg, 0);
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL)
        {
            // Cancel button
            EndDialog(hDlg, 0);
        }
        return (INT_PTR)TRUE;
    case WM_HSCROLL:
        pos = GetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1), IDC_SCROLLBAR1);
        //pos = GetScrollPos(hDlg, SB_CTL);
        switch (LOWORD(wParam))
        {
            case SB_LINELEFT:      //натиснуто кнопку ліворуч
                pos--;
                break;
            case SB_LINERIGHT:      //натиснуто кнопку праворуч
                pos++;
                break;
            case SB_THUMBPOSITION: //фіксована позиція повзуна
            case SB_THUMBTRACK:    //поточна позиція повзуна
                pos = HIWORD(wParam);
                break;
            default:
                break;
        }
        //... потрібний код
        //pos = GetScrollPos(hDlg, SB_CTL);
        SetScrollPos(hDlg, IDC_SCROLLBAR1,127,TRUE);  //фіксація повзуна
        //SetDlgItemText(hDlg, IDC_STATIC_MOD1, (LPCSTR)pos);
        //... потрібний код
        break;
        default:
        // do nothing
            break;
    }
    return (INT_PTR)FALSE;
}
