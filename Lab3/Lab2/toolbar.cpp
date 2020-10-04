#include "framework.h"
#include "pch.h"
#include "lab3.h"
#include "toolbar.h"
#include "resource1.h"
#include <iostream>

HWND hwndToolBar = NULL;
int point, line, rectangle, ellipse, currentButton = 0;
const int allShapes = 5;
int shapes[allShapes] = { point ,line ,rectangle ,ellipse ,currentButton };

void OnCreate(HWND hWnd)
{
    TBBUTTON tbb[5];
    ZeroMemory(tbb, sizeof(tbb));
    tbb[0].iBitmap = 0;
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = TBSTYLE_BUTTON;
    tbb[0].idCommand = ID_TOOL_POINT;
    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = ID_TOOL_LINE;
    tbb[2].iBitmap = 2; //індекс зображення у BITMAP
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_TOOL_RECTANGLE;
    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_TOOL_ELLIPSE;
    tbb[4].iBitmap = 4;
    tbb[4].fsState = TBSTATE_ENABLED;
    tbb[4].fsStyle = TBSTYLE_SEP; //роздільник груп кнопок
    tbb[4].idCommand = 0;
    hwndToolBar = CreateToolbarEx(hWnd,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR,
        4, //кількість зображень у BITMAP
        hInst,
        IDB_BITMAP1, //ID ресурсу BITMAP
        tbb,
        5, //кількість кнопок (разом з роздільником)
        24, 24, 24, 24, //розміри кнопок та зображень BITMAP
        sizeof(TBBUTTON));
}

//---обробник повідомлення WM_SIZE---
void OnSize(HWND hWnd)
{
    RECT rc, rw;
    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc); //нові розміри головного вікна
        GetWindowRect(hwndToolBar, &rw); //нам потрібно знати висоту Toolbar
        MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
    }
}

static void UnPress(int button)
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, currentButton, 0);

    currentButton = button;
}

void SetToZeros()
{
    for (auto& item : shapes)
    {
        item = 0;
    }
}

void OnToolPoint(HWND hWnd)
{
    void SetToZeros();

    point = !point;

    UnPress(ID_TOOL_POINT);

    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_POINT, point);
}

void OnToolLine(HWND hWnd)
{
    void SetToZeros();

    line = !line;

    UnPress(ID_TOOL_LINE);

    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_LINE, line);
}

void OnToolRectangle(HWND hWnd)
{
    void SetToZeros();

    rectangle = !rectangle;

    UnPress(ID_TOOL_RECTANGLE);

    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RECTANGLE, rectangle);
}

void OnToolEllipse(HWND hWnd)
{
    void SetToZeros();

    ellipse = !ellipse;

    UnPress(ID_TOOL_ELLIPSE);

    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ELLIPSE, ellipse);
}

void OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LPNMHDR pnmh = (LPNMHDR)lParam;
    LPCSTR pText;
    if (pnmh->code == TTN_NEEDTEXT)
    {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom)
        {
        case ID_TOOL_POINT:
            pText = "Крапка";
            break;
        case ID_TOOL_LINE:
            pText = "Лінія";
            break;
        case ID_TOOL_RECTANGLE:
            pText = "Прямокутник";
            break;
        case ID_TOOL_ELLIPSE:
            pText = "Овал";
            break;
        default: pText = "Щось невідоме";
        }
        lstrcpy(lpttt->szText, pText);
    }
}
