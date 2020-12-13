// Lab1.cpp : Defines the input point for the application.
//
// First Part

#include "framework.h"
#include "pch.h"
#include "Object2.h"
#include <vector>
#include <random>
#include "Resource.h"

#define MAX_LOADSTRING 100

#pragma region VariablesAndFunctions

// Global variables:
HINSTANCE hInst;                                // Current instance
WCHAR szTitle[MAX_LOADSTRING];                  // Header row text
WCHAR szWindowClass[MAX_LOADSTRING];            // Class name of main window

// Send declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
std::vector<std::vector<int>> MakeMatrix(int, int, int, HWND);
BOOL ParseFromCmd();

LPWSTR* szArglist;
int nArgs;

int const allValues = 3;
int values_MOD2[allValues];

int n_MOD2;
int Min_MOD2;
int Max_MOD2;

std::vector<std::vector<int>> matrix(n_MOD2, std::vector<int>(n_MOD2));

#pragma endregion VariablesAndFunctions

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
    LoadStringW(hInstance, IDC_OBJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OBJECT2));

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

    ParseFromCmd();

    //Compiler version g++ 6.3.0

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_OBJECT2));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_OBJECT2);
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

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

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
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
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
    //case WM_PAINT:
    //    PAINTSTRUCT ps;
    //    UpdateWindow(hWnd);
    //    HDC hdc = BeginPaint(hWnd, &ps);

    //    //matrix = MakeMatrix(n_MOD2, Min_MOD2, Max_MOD2, hWnd);

    //    //for (size_t i = 0; i < sizeof(matrix); i++)
    //    //{
    //    //    for (size_t j = 0; j < sizeof(matrix); j++)
    //    //    {
    //    //        LPCWSTR temp = (LPCWSTR)matrix[i][j];
    //    //        TextOut(hdc, 0 + i, 0 + j, temp, 1);
    //    //    }
    //    //}

    //    EndPaint(hWnd, &ps);
    //    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}

BOOL ParseFromCmd()
{
    // parsing from command line
    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    if (NULL == szArglist)
    {
        // CommandLineToArgvW failed
        return FALSE;
    }
    else
    {
        for (int i = 0; i < nArgs; i++)
        {
            values_MOD2[i] = (int)szArglist[i];
        }

        n_MOD2 = values_MOD2[0];
        Min_MOD2 = values_MOD2[1];
        Max_MOD2 = values_MOD2[2];
    }

    // Free memory allocated for CommandLineToArgvW arguments.

    LocalFree(szArglist);
}

int RandomInt(int low, int high)
{
    std::random_device rd;
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(low, high);
    return distr(gen);
}

std::vector<std::vector<int>> MakeMatrix (int size, 
    int lower, int upper, HWND hDlg)
{
    std::vector<std::vector<int>> res;
    for (int i = 0; i < size; ++i)
    {
        auto a = std::vector<int>(size);
        for (int j = 0; j < size; ++j)
        {
            a[j] = RandomInt(lower, upper);
            //TextOut(hdc, textHeightPosition, textWidthPosition, "       ", 7);
        }
        res.push_back(a);
    }
    return res;
}

#pragma endregion ModifiedFuntions
