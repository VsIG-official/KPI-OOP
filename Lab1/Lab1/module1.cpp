#include "pch.h"
#include "framework.h"
#include "module1.h"
#include <iostream>

int cchMax;
LPSTR buffer; //LPCSTR
UINT result;

//Callback-������� ����
static BOOL CALLBACK MyWork_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM,HDC hdc)
{
    switch (iMessage)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            //... �������, ���� ��
            //������� ���� �������� Edit Control � �����
            UpdateWindow(hDlg);
            result = GetDlgItemTextA(hDlg, IDC_EDIT1, buffer, 255);
            //buffer = "some";
            //MessageBox(NULL, buffer, "Error message", 14);

            TextOut(hdc, TA_CENTER, TA_CENTER, (LPSTR)result, 255);

            //... �������, ���� ��
            break;
        }
        if (LOWORD(wParam) == IDCANCEL)
            EndDialog(hDlg, 0);
        break;
    default: break;
    }
    return FALSE;
}
