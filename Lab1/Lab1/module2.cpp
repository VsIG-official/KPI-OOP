#include "pch.h"
#include "framework.h"
#include "module3.h"
#include "module2.h"
#include "Resource.h"

#pragma region FunctionsDeclaration

static void OnNext(HWND hDlg);
static void OnCancel(HWND hDlg);
static void OnClose(HWND hDlg);

static INT_PTR CALLBACK Work_MOD2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

#pragma endregion

#pragma region Functions

/// <summary>
/// dialog box creation function
/// </summary>
/// <param name="hInst">The hinst.</param>
/// <param name="hWnd">The hWND.</param>
/// <returns></returns>
int Func_MOD2(HINSTANCE hInst, HWND hWnd)
{
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_WORK1_MOD2), hWnd, Work_MOD2);
}

/// <summary>
/// Callback-function for first dialog window
/// </summary>
/// <param name="hDlg">The h dialog.</param>
/// <param name="message">The message.</param>
/// <param name="wParam">The w parameter.</param>
/// <param name="lParam">The l parameter.</param>
/// <returns></returns>
INT_PTR CALLBACK Work_MOD2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_CANCEL1_MOD2:
            OnCancel(hDlg);
            return (INT_PTR)TRUE;
        case IDC_NEXT_MOD2:
            OnNext(hDlg);
            return (INT_PTR)TRUE;
        }
        break;
    case WM_CLOSE:
    {
        OnClose(hDlg);
    }
    break;
    }
    return (INT_PTR)FALSE;
}

/// <summary>
/// Called when IDC_NEXT_MOD2 clicked
/// </summary>
/// <param name="hDlg">The dialog.</param>
void OnNext(HWND hDlg)
{
    EndDialog(hDlg, 1);

    Func_MOD3(hInst, hDlg);
}

/// <summary>
/// Called when IDC_CANCEL1_MOD2 clicked
/// </summary>
/// <param name="hDlg">The dialog.</param>
void OnCancel(HWND hDlg)
{
    EndDialog(hDlg, 0);
}

/// <summary>
/// Called when window is closing
/// </summary>
/// <param name="hDlg">The dialog.</param>
void OnClose(HWND hDlg)
{
    EndDialog(hDlg, 0);
}

#pragma endregion
