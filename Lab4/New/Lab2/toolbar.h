#pragma once

#define ID_TOOL_POINT                   32805
#define ID_TOOL_LINE                    32806
#define ID_TOOL_RECTANGLE               32807
#define ID_TOOL_ELLIPSE                 32809
#define IDC_MY_TOOLBAR                  32811

/// <summary>
/// Toolbar class for creating toolbar
/// </summary>
class Toolbar
{
private:
	static void SetToZeros();
	static void SetToOpposite(int value);
	static void ChangeButton(int button, int shape);
public:
	void OnSize(HWND hWnd);
	void OnCreate(HWND hWnd);
	void OnNotify(HWND hWnd, LPARAM lParam);
	void OnToolPoint();
	void OnToolLine();
	void OnToolRectangle();
	void OnToolEllipse();
};
