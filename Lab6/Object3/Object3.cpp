﻿// Object3.cpp : Defines the input point for the application.
//
// First Part

#include "framework.h"
#include "pch.h"
#include "Object3.h"
#include "Resource.h"
#include <string>
#include <vector>
#include <iostream>
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
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rc = { 0 };
        GetClientRect(hWnd, &rc);
        UpdateWindow(hWnd);

        //std::string tempBufferForMatrixString = bufferText;
        
        TextOutA(hdc, 0 , 0 , bufferText, sizeof(bufferText));

        //// dynamic allocation
        //int** matrix = new int* [n_MOD3];
        //for (int i = 0; i < n_MOD3; ++i)
        //{
        //    matrix[i] = new int[n_MOD3];
        //}

        //std::string num;

        //// fill
        //for (int i = 0; i < n_MOD3; ++i)
        //{
        //    for (int j = 0; j < n_MOD3; ++j)
        //    {
        //        num = tempBufferForMatrixString.substr(0,
        //            tempBufferForMatrixString.find_first_of(" "));

        //        buffer.push_back(stod(num));

        //        tempBufferForMatrixString = tempBufferForMatrixString.substr(
        //            tempBufferForMatrixString.find_first_of(" ") + 1);

        //        matrix[i][j] = buffer[i];

        //        char* some;

        //        //_itoa_s(()matrix[i][j], some, 20, 2);
        //        //TextOutA(hdc,0+i,0+j, (LPCSTR)buffer[i],1);
        //        //DrawTextA(hdc, (LPCSTR)matrix[i][j], i+2, &rc, DT_TOP);
        //    }
        //}

        ////int num1, num2, det = 1, index,
        ////    total = 1; // Initialize result

        ////// temporary array for storing row
        ////int** tempArr = new int* [n_MOD3 + 1];

        ////int temp;

        //////// loop for traversing the diagonal elements
        ////for (int i = 0; i < n_MOD3; i++)
        ////{
        ////    index = i; // initialize the index

        ////    // finding the index which has non zero value
        ////    while (matrix[index][i] == 0 && index < n_MOD3)
        ////    {
        ////        index++;
        ////    }
        ////    if (index == n_MOD3) // if there is non zero element
        ////    {
        ////        // the determinat of matrix as zero
        ////        continue;
        ////    }
        ////    if (index != i)
        ////    {
        ////        // loop for swaping the diagonal element row and
        ////        // index row
        ////        for (int j = 0; j < n_MOD3; j++)
        ////        {
        ////            swap(matrix[index][j], matrix[i][j]);
        ////        }
        ////        // determinant sign changes when we shift rows
        ////        // go through determinant properties
        ////        det = det * pow(-1, index - i);
        ////    }

        ////    // storing the values of diagonal row elements
        ////    for (int j = 0; j < n_MOD3; j++)
        ////    {
        ////        tempArr[j] = (int*)matrix[i][j];
        ////    }
        ////    // traversing every row below the diagonal element
        ////    for (int j = i + 1; j < n_MOD3; j++)
        ////    {
        ////        num1 = (int)tempArr[i]; // value of diagonal element
        ////        num2 = matrix[j][i]; // value of next row element

        ////        // traversing every column of row
        ////        // and multiplying to every row
        ////        for (int k = 0; k < n_MOD3; k++)
        ////        {
        ////            // multiplying to make the diagonal
        ////            // element and next row element equal
        ////            matrix[j][k]
        ////                = (num1 * matrix[j][k]) - (num2 * (int)tempArr[k]);
        ////        }
        ////        total = total * num1; // Det(kA)=kDet(A);
        ////    }
        ////    int temp = det;

        ////    temp = det * matrix[i][i];
        ////}


        //// mulitplying the diagonal elements to get determinant
        ////for (int i = 0; i < n_MOD3; i++)
        ////{
        ////    temp = det * matrix[i][i];
        ////}
        ////determinant = (temp / total); // Det(kA)/k=Det(A);

        //// free
        //for (int i = 0; i < n_MOD3; ++i)
        //{
        //    delete[] matrix[i];
        //}
        //delete[] matrix;

        //char* cstr = new char[copyMatrix.size() + 1];
        //strcpy_s(cstr, copyMatrix.size() + 1, copyMatrix.c_str());


        EndPaint(hWnd, &ps);
    }

        break;
    default:
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}

/// <summary>
/// Calculates determinant
/// </summary>
/// <param name="hWnd"></param>
void CalculateDeterminant(HWND hWnd)
{
    
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
