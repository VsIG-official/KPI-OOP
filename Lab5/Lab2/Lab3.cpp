// Lab1.cpp : Defines the input point for the application.
//
// First Part

#include "framework.h"
#include "pch.h"
#include "Lab3.h"
#include "Resource.h"
#include "my_editor.h"
#include "toolbar.h"
#include "my_table.h"

#define MAX_LOADSTRING 100

#pragma region VariablesAndFunctions

// Global variables:
HINSTANCE hInst;                                // Current instance
WCHAR szTitle[MAX_LOADSTRING];                  // Header row text
WCHAR szWindowClass[MAX_LOADSTRING];            // Class name of main window

LPCSTR currentShape;
const LPCSTR POINT_NAME = "Крапка";
const LPCSTR LINE_NAME = "Лінія";
const LPCSTR RECTANGLE_NAME = "Прямокутник";
const LPCSTR ELLIPSE_NAME = "Овал";
const LPCSTR LINEOO_NAME = "Лінія з кружочками на кінцях";
const LPCSTR CUBE_NAME = "Куб";
string detailsOfShape;
wchar_t* stringForShape[1024];

Toolbar toolbar;
MyEditor& ED = ED.getInstance();
MyTable* table = new MyTable;
HWND hwnd = NULL;

// Send declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
static void CallToolPoint();
static void CallToolLine();
static void CallToolRectangle();
static void CallToolEllipse();
static void CallToolLineOO();
static void CallToolCube();
static void OnWMCreateCall(HWND);
BOOL CALLBACK Table(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

    InitCommonControls();
    // TODO: Place the code here.

    // Global line initialization
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB3);
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
        OnWMCreateCall(hWnd);
        break;
    case WM_SIZE: // this message is sent if the window resizes
        toolbar.OnSize(hWnd);
        break;
    case WM_NOTIFY: // message from the buttons
        toolbar.OnNotify(hWnd, lParam);
        break;
    case WM_LBUTTONDOWN:
        ED.OnLBdown(hWnd);
        break;
    case WM_LBUTTONUP:
        ED.OnLBup(hWnd);
        *stringForShape = ED.GetDetails();
        table->Add(hwnd, stringForShape);
        break;
    case WM_MOUSEMOVE:
        ED.OnMouseMove(hWnd);
        break;
    case WM_PAINT:
        ED.OnPaint(hWnd);
        break;
    case WM_INITMENUPOPUP:
        ED.OnInitMenuPopup(hWnd, wParam);
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDD_TABLE:
            hwnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TABLE), 0, Table);
            ShowWindow(hwnd, SW_SHOW);
            SetWindowTextA(hwnd, "Таблиця");
            break;
        case ID_TOOL_POINT:
            CallToolPoint();
            break;
        case ID_TOOL_LINE:
            CallToolLine();
            break;
        case ID_TOOL_RECTANGLE:
            CallToolRectangle();
            break;
        case ID_TOOL_ELLIPSE:
            CallToolEllipse();
            break;
        case ID_TOOL_LINEOO:
            CallToolLineOO();
            break;
        case ID_TOOL_CUBE:
            CallToolCube();
            break;
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
    default:
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}

/// <summary>
/// Do something when WM_CREATE is called
/// </summary>
void OnWMCreateCall(HWND hWnd)
{
    toolbar.OnCreate(hWnd); // here we will create Toolbar
    CallToolPoint();
}

/// <summary>
/// Do something when Point tool is used
/// </summary>
void CallToolPoint()
{
    toolbar.OnToolPoint();
    ED.Start(new PointShape);
}

/// <summary>
/// Do something when Line tool is used
/// </summary>
void CallToolLine()
{
    toolbar.OnToolLine();
    ED.Start(new LineShape);
}

/// <summary>
/// Do something when Rectangle tool is used
/// </summary>
void CallToolRectangle()
{
    toolbar.OnToolRectangle();
    ED.Start(new RectangleShape);
}

/// <summary>
/// Do something when Ellipse tool is used
/// </summary>
void CallToolEllipse()
{
    toolbar.OnToolEllipse();
    ED.Start(new EllipseShape);
}

/// <summary>
/// Do something when LineOO tool is used
/// </summary>
void CallToolLineOO()
{
    toolbar.OnToolLineOO();
    ED.Start(new LineOOShape);
}

/// <summary>
/// Do something when Cube tool is used
/// </summary>
void CallToolCube()
{
    toolbar.OnToolCube();
    ED.Start(new CubeShape);
}

BOOL CALLBACK Table(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    string path = "./objects.txt";
    ifstream f;
    switch (uMsg)
    {
    case WM_INITDIALOG:
        f.open(path);
        if (!f.is_open())
        {
            throw new exception("Can't open the file");
        }
        else
        {
            string str;
            while (!f.eof())
            {
                str = "";
                //getline(f, str);
                if (str != "") SendDlgItemMessage(hWnd, IDC_LIST, LB_ADDSTRING, 0, (LPARAM)str.c_str());
            }
        }
        f.close();
        return (INT_PTR)TRUE;
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDCLEAR)
        {
            std::ofstream clear;
            clear.open(path, std::ofstream::out | std::ofstream::trunc);
            clear.close();
            SendDlgItemMessage(hWnd, IDC_LIST, LB_RESETCONTENT, 0, 0);
        }
        if (LOWORD(wParam) == IDCANCEL)
        {
            DestroyWindow(hWnd);
            return TRUE;
        }
    }
    return (INT_PTR)FALSE;
}


#pragma endregion ModifiedFuntions
