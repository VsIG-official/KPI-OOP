#include "pch.h"
#include "framework.h"
#include "module2.h"
#include "Resource.h"

// First callback
INT_PTR CALLBACK Work1_MOD2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_CANCEL1_MOD2:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        case IDC_NEXT_MOD2:
            EndDialog(hDlg, LOWORD(wParam));
            DialogBox(hInst, MAKEINTRESOURCE(IDD_WORK2_MOD2), hDlg, Work2_MOD2);
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// Second callback
INT_PTR CALLBACK Work2_MOD2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_OK2_MOD2:       // Next button
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        case IDC_CANCEL2_MOD2:   // Cancel button
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        case IDC_BACK_MOD2:     // Back button
            EndDialog(hDlg, LOWORD(wParam));
            DialogBox(hInst, MAKEINTRESOURCE(IDD_WORK1_MOD2), hDlg, Work1_MOD2);
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}