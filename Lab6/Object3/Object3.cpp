// Object3.cpp : Defines the input point for the application.
//
// First Part

#include "framework.h"
#include "pch.h"
#include "Object3.h"
#include "Resource.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_LOADSTRING 100

#pragma region VariablesAndFunctions

// Global variables:
HINSTANCE hInst;                                // Current instance
WCHAR szTitle[MAX_LOADSTRING];                  // Header row text
WCHAR szWindowClass[MAX_LOADSTRING];            // Class name of main window

char bufferText[1024];
int n_MOD3;
std::vector<int> buffer;
int determinant;

// Send declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
long GetTextFromClipboard(HWND, char*, long);
void CalculateDeterminant(HWND hWnd);
void OnCopyData(HWND hWnd, WPARAM wParam, LPARAM lParam);
void GetMatrixWithoutRowAndCol(int** matrix, int size, int row, int col, int** newMatrix);
int MatrixDeterminant(int** matrix, int size);

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
    LoadStringW(hInstance, IDC_OBJECT3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OBJECT3));

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_OBJECT3));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_OBJECT3);
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
    case WM_CREATE:
    {
        GetTextFromClipboard(hWnd, bufferText, sizeof(bufferText));

        SetWindowPos(hWnd, HWND_BOTTOM, 141, 40, 400, 300, SWP_DEFERERASE);
    }
        break;
    case WM_COPYDATA:
    {
        OnCopyData(hWnd, wParam, lParam);

        CalculateDeterminant(hWnd);

        InvalidateRect(hWnd, 0, TRUE);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProcW(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        UpdateWindow(hWnd);
        HDC hdc = BeginPaint(hWnd, &ps);

        //bufferForDraw = (TCHAR)determinant;
        wchar_t value[50];
        //_itoa_s(determinant, bufferForDraw, sizeof(determinant), 10);

        wsprintfW(value, L"%d", (int)determinant);
        TextOut(hdc, 10, 10, value, lstrlen(value));

        EndPaint(hWnd, &ps);
    }

        break;
    default:
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}

/// <summary>
/// Calculate determinant
/// </summary>
/// <param name="matrix"></param>
/// <param name="size"></param>
/// <returns></returns>
int MatrixDeterminant(int** matrix, int size)
{
    int det = 0;
    int degree = 1;

    if (size == 1)
    {
        return matrix[0][0];
    }

    else if (size == 2)
    {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    else
    {
        int** newMatrix = new int* [size - 1];
        for (int i = 0; i < size - 1; i++)
        {
            newMatrix[i] = new int[size - 1];
        }

        for (int j = 0; j < size; j++)
        {
            GetMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

            det = det + (degree * matrix[0][j] * MatrixDeterminant(newMatrix, size - 1));

            degree = -degree;
        }

        for (int i = 0; i < size - 1; i++)
        {
            delete[] newMatrix[i];
        }
        delete[] newMatrix;
    }

    return det;
}

/// <summary>
/// Gets matrix without row and column
/// </summary>
/// <param name="matrix"></param>
/// <param name="size"></param>
/// <param name="row"></param>
/// <param name="col"></param>
/// <param name="newMatrix"></param>
void GetMatrixWithoutRowAndCol(int** matrix, int size, int row, int col, int** newMatrix)
{
    int offsetRow = 0;
    int offsetCol = 0;
    for (int i = 0; i < size - 1; i++)
    {
        if (i == row)
        {
            offsetRow = 1;
        }

        offsetCol = 0;
        for (int j = 0; j < size - 1; j++)
        {
            if (j == col)
            {
                offsetCol = 1;
            }

            newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
        }
    }
}

/// <summary>
/// Calculates determinant
/// </summary>
/// <param name="hWnd"></param>
void CalculateDeterminant(HWND hWnd)
{
    // dynamic allocation
    int** matrix = new int* [n_MOD3];
    for (int i = 0; i < n_MOD3; ++i)
    {
        matrix[i] = new int[n_MOD3];
    }

    std::string tempBufferForMatrixString = bufferText;

    string currentNumber;

    std::replace(tempBufferForMatrixString.begin(),
        tempBufferForMatrixString.end(), '\n', ' ');

    while (tempBufferForMatrixString != "")
    {
        currentNumber = tempBufferForMatrixString.substr(
            0, tempBufferForMatrixString.find_first_of(" "));

        buffer.push_back(stod(currentNumber));

        tempBufferForMatrixString = tempBufferForMatrixString.substr(
            tempBufferForMatrixString.find_first_of(" ") + 1);
    }

    //fill
    for (int i = 0; i < n_MOD3; ++i)
    {
        for (int j = 0; j < n_MOD3; ++j)
        {
            matrix[i][j] = buffer[i];
        }
    }

    determinant = MatrixDeterminant(matrix, n_MOD3);

    // free
    for (int z = 0; z < n_MOD3; ++z)
    {
        delete[] matrix[z];
    }
    delete[] matrix;
}

/// <summary>
/// Copy the data from another window
/// </summary>
/// <param name="hWnd"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
void OnCopyData(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COPYDATASTRUCT* cds;
    cds = (COPYDATASTRUCT*)lParam;
    long* p = (long*)cds->lpData;
    n_MOD3 = p[0];
}

/// <summary>
/// Get text from Clipboard
/// </summary>
/// <param name="hWnd"></param>
/// <param name="dest"></param>
/// <param name="maxsize"></param>
long GetTextFromClipboard(HWND hWnd, char* dest, long maxsize)
{
    HGLOBAL hglb;
    LPTSTR lptstr;
    long size, res;
    res = 0;
    if (!IsClipboardFormatAvailable(CF_TEXT)) return 0;
    if (!OpenClipboard(hWnd)) return 0;
    hglb = GetClipboardData(CF_TEXT);
    if (hglb != NULL)
    {
        lptstr = (LPTSTR)GlobalLock(hglb);
        if (lptstr != NULL)
        {
            size = strlen((char*)lptstr);
            if (size > maxsize)
            {
                lptstr[maxsize] = 0;
                size = strlen((char*)lptstr);
            }
            strcpy_s(dest, maxsize, (char*)lptstr);
            res = size;
            GlobalUnlock(hglb);
        }
    }
    CloseClipboard();
    return res;
}

#pragma endregion ModifiedFuntions
