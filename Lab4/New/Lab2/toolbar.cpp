#include "framework.h"
#include "pch.h"
#include "lab3.h"
#include "toolbar.h"
#include "resource1.h"

#pragma region Variables

HWND hwndToolBar = NULL;
int point, line, rectangle, ellipse, lineOO, cube, buttonToChange = 0;
const int allShapes = 7;
int shapes[allShapes] = { point, line, rectangle, ellipse,
                            lineOO, cube, buttonToChange };
const LPCSTR pointName = "Крапка";
const LPCSTR lineName = "Лінія";
const LPCSTR rectangleName = "Прямокутник";
const LPCSTR ellipseName = "Овал";
const LPCSTR lineOOName = "Лінія з кружочками на кінцях";
const LPCSTR cubeName = "Куб";
const LPCSTR unnkownName = "Щось невідоме";

#pragma endregion Variables

#pragma region Functions

/// <summary>
/// Creates toolbar
/// </summary>
/// <param name="hWnd"></param>
void Toolbar::OnCreate(HWND hWnd)
{
    TBBUTTON tbb[7];
    ZeroMemory(tbb, sizeof(tbb));
    tbb[0].iBitmap = 0;
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = TBSTYLE_BUTTON;
    tbb[0].idCommand = ID_TOOL_POINT;
    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = ID_TOOL_LINE;
    tbb[2].iBitmap = 2; // image index in BITMAP
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_TOOL_RECTANGLE;
    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_TOOL_ELLIPSE;
    tbb[4].iBitmap = 4;
    tbb[4].fsState = TBSTATE_ENABLED;
    tbb[4].fsStyle = TBSTYLE_BUTTON;
    tbb[4].idCommand = ID_TOOL_LINEOO;
    tbb[5].iBitmap = 5;
    tbb[5].fsState = TBSTATE_ENABLED;
    tbb[5].fsStyle = TBSTYLE_BUTTON; // separator of groups of buttons
    tbb[5].idCommand = ID_TOOL_CUBE;
    tbb[6].iBitmap = 6;
    tbb[6].fsState = TBSTATE_ENABLED;
    tbb[6].fsStyle = TBSTYLE_SEP; // separator of groups of buttons
    tbb[6].idCommand = 0;

    hwndToolBar = CreateToolbarEx(hWnd,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR,
        6, // number of images in BITMAP
        hInst,
        IDB_BITMAP1, // BITMAP resource ID
        tbb,
        7, // number of buttons (with separator)
        24, 24, 24, 24, // BITMAP button and image sizes
        sizeof(TBBUTTON));
}

// --- message handler WM_SIZE ---
/// <summary>
/// Change size of toolbar
/// </summary>
/// <param name="hWnd"></param>
void Toolbar::OnSize(HWND hWnd)
{
    RECT rc, rw;
    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc); // new dimensions of the main window
        GetWindowRect(hwndToolBar, &rw); // we need to know the height of the Toolbar
        MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
    }
}

/// <summary>
/// UnClick button and click button
/// </summary>
/// <param name="button"> button to unclick/click </param>
/// <param name="shape"> shape element </param>
void Toolbar::ChangeButton(int button, int shape)
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, buttonToChange, 0);

    buttonToChange = button;

    SendMessage(hwndToolBar, TB_PRESSBUTTON, buttonToChange, shape);
}

/// <summary>
/// Set all elements to zero
/// </summary>
void Toolbar::SetToZeros()
{
    for (auto& item : shapes)
    {
        item = 0;
    }
}

/// <summary>
/// Sets value to opposite value
/// </summary>
/// <param name="value"></param>
void Toolbar::SetToOpposite(int value)
{
    shapes[value] = !shapes[value];
}

/// <summary>
/// Function for drawing points with buttons animation
/// </summary>
void Toolbar::OnToolPoint()
{
    SetToZeros();

    SetToOpposite(0);

    ChangeButton(ID_TOOL_POINT, shapes[0]);
}

/// <summary>
/// Function for drawing lines with buttons animation
/// </summary>
void Toolbar::OnToolLine()
{
    SetToZeros();

    SetToOpposite(1);

    ChangeButton(ID_TOOL_LINE, shapes[1]);
}

/// <summary>
/// Function for drawing rectangles with buttons animation
/// </summary>
void Toolbar::OnToolRectangle()
{
    SetToZeros();

    SetToOpposite(2);

    ChangeButton(ID_TOOL_RECTANGLE, shapes[2]);
}

/// <summary>
/// Function for drawing ellipses with buttons animation
/// </summary>
void Toolbar::OnToolEllipse()
{
    SetToZeros();

    SetToOpposite(3);

    ChangeButton(ID_TOOL_ELLIPSE, shapes[3]);
}

/// <summary>
/// Function for drawing lines with ellipses with buttons animation
/// </summary>
void Toolbar::OnToolLineOO()
{
    SetToZeros();

    SetToOpposite(4);

    ChangeButton(ID_TOOL_LINEOO, shapes[4]);
}

/// <summary>
/// Function for drawing cubes with buttons animation
/// </summary>
void Toolbar::OnToolCube()
{
    SetToZeros();

    SetToOpposite(5);

    ChangeButton(ID_TOOL_CUBE, shapes[5]);
}

/// <summary>
/// Function for tooltips
/// </summary>
/// <param name="hWnd"></param>
/// <param name="lParam"></param>
void Toolbar::OnNotify(HWND hWnd, LPARAM lParam)
{
    LPNMHDR pnmh = (LPNMHDR)lParam;
    LPCSTR pText;
    if (pnmh->code == TTN_NEEDTEXT)
    {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom)
        {
        case ID_TOOL_POINT:
            pText = pointName;
            break;
        case ID_TOOL_LINE:
            pText = lineName;
            break;
        case ID_TOOL_RECTANGLE:
            pText = rectangleName;
            break;
        case ID_TOOL_ELLIPSE:
            pText = ellipseName;
            break;
        default: pText = unnkownName;
        }
        lstrcpy(lpttt->szText, pText);
    }
}

#pragma endregion Functions
