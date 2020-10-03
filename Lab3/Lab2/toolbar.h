#pragma once

#define ID_TOOL_POINT                   32805
#define ID_TOOL_LINE                    32806
#define ID_TOOL_RECTANGLE               32807
#define ID_TOOL_ELLIPSE                 32809
#define IDC_MY_TOOLBAR                  32811

void OnSize(HWND hWnd);
void OnCreate(HWND hWnd);
void OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
void OnToolPoint(HWND hWnd, int currentPress);
