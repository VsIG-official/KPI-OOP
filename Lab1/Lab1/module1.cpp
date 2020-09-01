#include "pch.h"
#include "framework.h"
#include "resource1.h"


LPTSTR buffer;
int cchMax;

//Callback-������� ����
static BOOL CALLBACK Work1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM)
{
    switch (iMessage)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            //... �������, ���� ��

             //������� ���� �������� Edit Control � �����
            GetDlgItemText(hDlg, IDC_EDIT1, buffer, cchMax);

            //... �������, ���� ��
            EndDialog(hDlg, 1);
            break;
        }
        if (LOWORD(wParam) == IDCANCEL)
            EndDialog(hDlg, 0);
        break;
    default:
        break;
    }
    return FALSE;
}
