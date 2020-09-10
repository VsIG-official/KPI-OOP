#include "pch.h"
#include "framework.h"
#include "module3.h"
#include "module2.h"
#include "Resource.h"

#pragma region FunctionsDeclaration

static void OnBack(HWND hDlg);

static INT_PTR CALLBACK Work2_MOD2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

#pragma endregion

#pragma region Functions

/// <summary>
/// dialog box creation function
/// </summary>
/// <param name="hInst">The hinst.</param>
/// <param name="hWnd">The hWND.</param>
/// <returns></returns>
int Func_MOD3(HINSTANCE hInst, HWND hWnd)
{
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_WORK2_MOD2), hWnd, Work2_MOD2);
}

/// <summary>
/// Callback-function for second dialog window
/// </summary>
/// <param name="hDlg">The h dialog.</param>
/// <param name="message">The message.</param>
/// <param name="wParam">The w parameter.</param>
/// <param name="lParam">The l parameter.</param>
/// <returns></returns>
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
            EndDialog(hDlg, 0);
            DefWindowProc(hDlg, message, wParam, lParam);
            return (INT_PTR)TRUE;
        case IDC_BACK_MOD2:     // Back button
            OnBack(hDlg);
            return (INT_PTR)TRUE;
        }
        break;
    case WM_CLOSE:
    {
        EndDialog(hDlg, 0);
    }
    break;
    }
    return (INT_PTR)FALSE;
}

/// <summary>
/// Called when IDC_BACK_MOD2 clicked
/// </summary>
/// <param name="hDlg">The dialog.</param>
void OnBack(HWND hDlg)
{
    EndDialog(hDlg, 1);

    Func_MOD2(hInst, hDlg);
}

#pragma endregion