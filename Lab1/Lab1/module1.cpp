﻿#include "pch.h"
#include "framework.h"
#include "module1.h"

#pragma region VariablesAndFunctionsDeclarations

static int const maxSymbols_MOD1 = 255;
char tempPlaceForText_MOD1[maxSymbols_MOD1] = { 0 };

int pos_MOD1;
static int nMinPos_MOD1 = 1;
static int nMaxPos_MOD1 = 100;
static HWND hWndScrollBar_MOD1;
BOOL canWrite_MOD1 = FALSE;
int numOfDig_MOD1;

static INT_PTR CALLBACK Work1_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
static void OnInit_MOD1(HWND hDlg);
static void OnLineLeft_MOD1(HWND hDlg);
static void OnLineRight_MOD1(HWND hDlg);
static void OnOkMod2_MOD1(HWND hDlg);
static void OnThumbPosAndTrack_MOD1(HWND hDlg, WPARAM wParam);
static int Count_MOD1(int pos_MOD1);

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
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_WORK_MOD1), hWnd, Work1_MOD1);
}

/// <summary>
/// Callback-function for hor.scrollbar
/// </summary>
/// <param name="hDlg"></param>
/// <param name="iMessage"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
INT_PTR CALLBACK Work1_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_INITDIALOG:
        OnInit_MOD1(hDlg);
        break;
    case WM_HSCROLL:
        pos_MOD1 = GetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1_MOD1), SB_CTL);
        switch (LOWORD(wParam))
        {
        case SB_LINELEFT:
            OnLineLeft_MOD1(hDlg);
            break;
        case SB_LINERIGHT:
            OnLineRight_MOD1(hDlg);
            break;
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            OnThumbPosAndTrack_MOD1(hDlg, wParam);
            break;
        default: break;
        }
        SetScrollPos(hWndScrollBar_MOD1, SB_CTL, pos_MOD1, TRUE);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            OnOkMod2_MOD1(hDlg);
            return (INT_PTR)TRUE;
            break;
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
        break;
    default: break;
    }
    return FALSE;
}

/// <summary>
/// Called on initializing
/// </summary>
/// <param name="hDlg">The dialog.</param>
void OnInit_MOD1(HWND hDlg)
{
    hWndScrollBar_MOD1 = GetDlgItem(hDlg, IDC_SCROLLBAR1_MOD1);
    pos_MOD1 = 1;
    SetScrollRange(hWndScrollBar_MOD1, SB_CTL, nMinPos_MOD1, nMaxPos_MOD1, TRUE);
}

/// <summary>
/// Called when scroll pos goes to the left.
/// </summary>
/// <param name="hDlg">The dialog.</param>
void OnLineLeft_MOD1(HWND hDlg)
{
    if (pos_MOD1 != nMinPos_MOD1)
    {
        pos_MOD1--;
    }
    SetDlgItemInt(hDlg, IDC_STATIC_MOD1, pos_MOD1, TRUE);
}

/// <summary>
/// Called when scroll pos goes to the right.
/// </summary>
/// <param name="hDlg">The dialog.</param>
void OnLineRight_MOD1(HWND hDlg)
{
    if (pos_MOD1 != nMaxPos_MOD1)
    {
        pos_MOD1++;
    }
    SetDlgItemInt(hDlg, IDC_STATIC_MOD1, pos_MOD1, TRUE);
}

/// <summary>
/// Called when thumb position has changed
/// </summary>
/// <param name="hDlg">The h dialog.</param>
/// <param name="wParam">The w parameter.</param>
void OnThumbPosAndTrack_MOD1(HWND hDlg, WPARAM wParam)
{
    pos_MOD1 = HIWORD(wParam);
    SetDlgItemInt(hDlg, IDC_STATIC_MOD1, pos_MOD1, TRUE);
}

/// <summary>
/// Called when IDOK clicked
/// </summary>
/// <param name="hDlg">The dialog.</param>
void OnOkMod2_MOD1(HWND hDlg)
{
    canWrite_MOD1 = TRUE;
    numOfDig_MOD1 = Count_MOD1(pos_MOD1);
    EndDialog(hDlg, 1);
}

/// <summary>
/// Function to Count how many digits are in int
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
int Count_MOD1(int pos_MOD1)
{
    int count_MOD1 = 0;
    while (pos_MOD1 != 0)
    {
        pos_MOD1 = pos_MOD1 / 10;
        ++count_MOD1;
    }
    return count_MOD1;
}

#pragma endregion
