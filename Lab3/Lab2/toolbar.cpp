#include "framework.h"
#include "pch.h"
#include "lab3.h"
#include "toolbar.h"
#include "resource1.h"

HWND hwndToolBar = NULL;
int point, line, rectangle, ellipse = 0;

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
    tbb[2].iBitmap = 2; //������ ���������� � BITMAP
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_TOOL_RECTANGLE;
    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_TOOL_ELLIPSE;
    tbb[4].iBitmap = 4;
    tbb[4].fsState = TBSTATE_ENABLED;
    tbb[4].fsStyle = TBSTYLE_SEP; //��������� ���� ������
    tbb[4].idCommand = 4;
    hwndToolBar = CreateToolbarEx(hWnd,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR,
        4, //������� ��������� � BITMAP
        hInst,
        IDB_BITMAP1, //ID ������� BITMAP
        tbb,
        5, //������� ������ (����� � �����������)
        24, 24, 24, 24, //������ ������ �� ��������� BITMAP
        sizeof(TBBUTTON));
}

//---�������� ����������� WM_SIZE---
void OnSize(HWND hWnd)
{
    RECT rc, rw;
    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc); //��� ������ ��������� ����
        GetWindowRect(hwndToolBar, &rw); //��� ������� ����� ������ Toolbar
        MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
    }
}

void OnToolPoint(HWND hWnd)
{
    point = !point;

    line, rectangle, ellipse = 0;

    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_POINT, point);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, rectangle, 0);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, line, 0);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ellipse, 0);
}

void OnToolLine(HWND hWnd)
{
    line = !line;

    point, rectangle, ellipse = 0;

    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_LINE, line);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, point, 0);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, rectangle, 0);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ellipse, 0);
}

void OnToolRectangle(HWND hWnd)
{
    rectangle = !rectangle;

    point, line, ellipse = 0;

    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_LINE, rectangle);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, point, 0);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, line, 0);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ellipse, 0);
}

void OnToolEllipse(HWND hWnd)
{
    ellipse = !ellipse;

    line, rectangle, point = 0;

    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_POINT, ellipse);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, point, 0);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, line, 0);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, rectangle, 0);
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
            pText = "������";
            break;
        case ID_TOOL_LINE:
            pText = "˳��";
            break;
        case ID_TOOL_RECTANGLE:
            pText = "�����������";
            break;
        case ID_TOOL_ELLIPSE:
            pText = "����";
            break;
        default: pText = "���� �������";
        }
        lstrcpy(lpttt->szText, pText);
    }
}
