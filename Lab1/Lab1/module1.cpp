#include "pch.h"
#include "framework.h"
#include "module1.h"

int symbols;
LPTSTR buffer; //LPCSTR
HDC hdc;
UINT textToShow;

//Callback-������� ����
static BOOL CALLBACK MyWork_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM)
{
    switch (iMessage)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            //... �������, ���� ��
            //������� ���� �������� Edit Control � �����

            GetDlgItemText(hDlg, IDC_EDIT1, buffer, symbols);
            TextOut(hdc, TA_CENTER, TA_CENTER, buffer, symbols);

            //... �������, ���� ��
            break;
        }
        if (LOWORD(wParam) == IDCANCEL) EndDialog(hDlg, 0);
        break;
    case WM_PAINT:
        PAINTSTRUCT ps;

        // TODO: �������� ���� ����� ��� ����������, ������������ HDC...
        //TextOutW(hdc, 10, 10, buffer, 18);

    default: break;
    }
    return FALSE;
}
