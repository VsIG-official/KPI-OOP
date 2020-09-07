// Lab1.cpp : Defines the input point for the application.
//
// First Part
#include "pch.h"
#include "framework.h"
#include "Lab1.h"
#include "module1.h"
#include "module2.h"

#define MAX_LOADSTRING 100

#pragma region Variables

// Global variables:
HINSTANCE hInst;                                // Current instance
WCHAR szTitle[MAX_LOADSTRING];                  // Header row text
WCHAR szWindowClass[MAX_LOADSTRING];            // Class name of main window


// Send declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

static void Work1(HWND hWnd);      // Declaration of our function
static void Work2(HWND hWnd);      // Declaration of our function
static void DrawTextOnScreen(HWND hWnd);      // Declaration of our function

static int textHeightPosition = 0;
static int textWidthPosition = 0;

#pragma endregion

#pragma region DefaultFunctions

// Second Part
// Enter Point "wWinMain"
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place the code here.

    // Global line initialization
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1));

    MSG msg;

    // Main message cycle:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  OBJECTIVE: To register the window class.
// Text of Function
/// <summary>
/// Register the window class.
/// </summary>
/// <param name="hInstance">The h instance.</param>
/// <returns></returns>
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   OBJECTIVE: Saves the instance marker and creates the main window
//
//   COMMENTARIES:
//
//        In this function, the instance marker is saved in a global variable, and also
//        the main program window is created and displayed.
//
/// <summary>
/// Saves the instance marker and creates the main window
/// </summary>
/// <param name="hInstance">The h instance.</param>
/// <param name="nCmdShow">The n command show.</param>
/// <returns></returns>
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Save instance marker in global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

#pragma endregion

#pragma region ModifiedFuntions

// Third Part
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  OBJECTIVE: Processes messages in the main window.
//
//  WM_COMMAND  - Process the application menu
//  WM_PAINT    - Drawing of the main window
//  WM_DESTROY  - Send message about exit and return
//
//
/// <summary>
/// Processes messages in the main window.
/// </summary>
/// <param name="hWnd">The h WND.</param>
/// <param name="message">The message.</param>
/// <param name="wParam">The w parameter.</param>
/// <param name="lParam">The l parameter.</param>
/// <returns></returns>
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Disassemble the selection in the menu:
        switch (wmId)
        {
        case IDM_WORK_MOD1:
            // first menu
            Work1(hWnd);

            // The update region represents the portion of the window's
            // client area that must be redrawn.
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case IDM_WORK_MOD2:
            // second menu
            Work2(hWnd);

            // The update region represents the portion of the window's
            // client area that must be redrawn.
            InvalidateRect(hWnd, 0, TRUE);
            break;
        case IDM_ABOUT:
            // About Menu
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            // Exit menu
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        DrawTextOnScreen(hWnd);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Fourth Part
/// <summary>
/// Message handler for "About" window.
/// </summary>
/// <param name="hDlg">The h dialog.</param>
/// <param name="message">The message.</param>
/// <param name="wParam">The w parameter.</param>
/// <param name="lParam">The l parameter.</param>
/// <returns></returns>
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        // When window is created
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

        // When OK is clicked
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            // End dialog window
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

/// <summary>
/// Function-handler of the menu item "Work1"
/// </summary>
/// <param name="hWnd">The h WND.</param>
void Work1(HWND hWnd)
{
    // What we program here that will be done
    Func_MOD1(hInst,hWnd);
}

/// <summary>
/// Function-handler of the menu item "Work2"
/// </summary>
/// <param name="hWnd">The h WND.</param>
void Work2(HWND hWnd)
{
    // What we program here that will be done
    Func_MOD2(hInst, hWnd);
}

/// <summary>
/// Draws the text on screen.
/// </summary>
/// <param name="hWnd">hWND</param>
void DrawTextOnScreen(HWND hWnd)
{
    PAINTSTRUCT ps;
    UpdateWindow(hWnd);
    HDC hdc = BeginPaint(hWnd, &ps);

    if (canWrite_MOD1)
    {
        _itoa_s(pos_MOD1, tempPlaceForText_MOD1, sizeof(pos_MOD1), 10);
        canWrite_MOD1 = FALSE;
    }

    TextOut(hdc, textHeightPosition, textWidthPosition, "       ", 7);
    TextOut(hdc, textHeightPosition, textWidthPosition, tempPlaceForText_MOD1, numOfDig_MOD1);

    ZeroMemory(tempPlaceForText_MOD1, pos_MOD1);

    EndPaint(hWnd, &ps);
}

#pragma endregion
