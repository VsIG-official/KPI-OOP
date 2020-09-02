#include "pch.h"
#include "framework.h"
#include "module1.h"

int symbols;
LPTSTR buffer; //LPCSTR
//HDC hdc;
UINT textToShow;

//Callback-функція вікна
static BOOL CALLBACK MyWork_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM)
{
    switch (iMessage)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            //... можливо, щось ще
            //зчитуємо вміст елементу Edit Control у буфер

            GetDlgItemText(hDlg, IDC_EDIT1, buffer, symbols);

            //... можливо, щось ще
            break;
        }
        if (LOWORD(wParam) == IDCANCEL) EndDialog(hDlg, 0);
        break;
    case WM_PAINT:
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hDlg, &ps);

        SetTextColor(hdc, RGB(0, 0, 0)); //White text.

        TextOut(hdc, 0, 0, "We love nice pictures.", strlen("We love nice pictures.")); //Print it!

        ReleaseDC(hDlg, hdc);
        EndPaint(hDlg, &ps);
        break;
    }
    return FALSE;
}
