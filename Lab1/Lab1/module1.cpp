#include "pch.h"
#include "framework.h"
#include "module1.h"

int cchMax;
LPSTR buffer; //LPCSTR
HDC hdc;
UINT textToShow;
CHAR TEXT[] = { 0 };

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

            GetDlgItemText(hDlg, IDC_EDIT1, TEXT, 255);
            //buffer = "some";
            TextOut(hdc, TA_CENTER, TA_CENTER, TEXT, 255);

            //... �������, ���� ��
            break;
        }
        if (LOWORD(wParam) == IDCANCEL)
            EndDialog(hDlg, 0);
        break;
    case WM_PAINT:
        //PAINTSTRUCT ps;

        // TODO: �������� ���� ����� ��� ����������, ������������ HDC...
        //TextOutW(hdc, 10, 10, buffer, 18);

    default: break;
    }
    return FALSE;
}
