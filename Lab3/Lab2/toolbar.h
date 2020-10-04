#pragma once

#define ID_TOOL_POINT                   32805
#define ID_TOOL_LINE                    32806
#define ID_TOOL_RECTANGLE               32807
#define ID_TOOL_ELLIPSE                 32809
#define IDC_MY_TOOLBAR                  32811

extern void OnSize(HWND hWnd);
extern void OnCreate(HWND hWnd);
extern void OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
extern void OnToolPoint(HWND hWnd);
extern void OnToolLine(HWND hWnd);
extern void OnToolRectangle(HWND hWnd);
extern void OnToolEllipse(HWND hWnd);
