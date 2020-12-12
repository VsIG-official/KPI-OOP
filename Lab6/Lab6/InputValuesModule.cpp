#include "pch.h"
#include "framework.h"
#include "InputValuesModule.h"

#pragma region VariablesAndFunctionsDeclarations

static int n_MOD1;
static int Min_MOD1;
static int Max_MOD1;

const int allValues = 3;
int values[allValues] = { n_MOD1, Min_MOD1, Max_MOD1 };

static INT_PTR CALLBACK InputValues_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
static void OnOk(HWND hDlg);
static void OnCancel(HWND hDlg);
static void OnClose(HWND hDlg);

#pragma endregion

#pragma region Functions

/// <summary>
/// dialog box creation function
/// </summary>
/// <param name="hInst">The hinst.</param>
/// <param name="hWnd">The hWND.</param>
/// <returns></returns>
int Func_MOD1(HINSTANCE hInst, HWND hWnd)
{
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_INPUT), hWnd, InputValues_MOD1);
    //dest = tempPlaceForText_MOD1;
}

/// <summary>
/// Callback-function for calling window with inputs
/// </summary>
/// <param name="hDlg"></param>
/// <param name="iMessage"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
INT_PTR CALLBACK InputValues_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            OnOk(hDlg);
            return (INT_PTR)TRUE;
            break;
        case IDCANCEL:
            OnCancel(hDlg);
            return (INT_PTR)TRUE;
            break;
        }
        break;
    case WM_CLOSE:
    {
        OnClose(hDlg);
    }
    break;
    default: break;
    }
    return FALSE;
}

/// <summary>
/// Called when IDOK clicked
/// </summary>
/// <param name="hDlg">The dialog.</param>
void OnOk(HWND hDlg)
{
    n_MOD1 = GetDlgItemInt(hDlg, IDC_EDIT_N, NULL, FALSE);
    Min_MOD1 = GetDlgItemInt(hDlg, IDC_EDIT_MIN, NULL, FALSE);
    Max_MOD1 = GetDlgItemInt(hDlg, IDC_EDIT_MAX, NULL, FALSE);
}

/// <summary>
/// Called when IDCANCEL clicked
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