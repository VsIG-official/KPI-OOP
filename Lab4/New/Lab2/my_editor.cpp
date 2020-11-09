#include "framework.h"
#include "pch.h"
#include "my_editor.h"
#include "toolbar.h"

#pragma region Variables

const int Size_Of_Array = 110;
Shape* pcshape[Size_Of_Array];
int size = 0;
bool isPressed;
int const menuCount = 6;
int allMenus[menuCount] = { ID_TOOL_POINT, ID_TOOL_LINE, 
ID_TOOL_RECTANGLE, ID_TOOL_ELLIPSE, ID_TOOL_LINEOO, ID_TOOL_CUBE};

#pragma endregion Variables

#pragma region Functions

/// <summary>
/// Destructor
/// </summary>
MyEditor::~MyEditor()
{
	for (int i = 0; i < size; i++)
	{
		delete pcshape[i];
	}
	delete *pcshape;
}

/// <summary>
/// Starts new Shape
/// </summary>
/// <param name="shape"></param>
void MyEditor::Start(Shape* shape)
{
	pcshape[size] = shape;
}

/// <summary>
/// Do something, when LB is clicked
/// </summary>
/// <param name="hWnd"></param>
void MyEditor::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
	isPressed = true;
}

/// <summary>
/// Do something, when LB is unclicked
/// </summary>
/// <param name="hWnd"></param>
void MyEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = false;
	pcshape[size]->Set(x1, y1, x2, y2);
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
	pcshape[size] = pcshape[size - 1]->Copy();
}

/// <summary>
/// Do something, when mouse is moved
/// </summary>
/// <param name="hWnd"></param>
void MyEditor::OnMouseMove(HWND hWnd)
{
	if (isPressed)
	{
		POINT pt;
		HDC hdc = GetDC(hWnd);
		SetROP2(hdc, R2_NOTXORPEN);
		MoveToEx(hdc, x1, y1, NULL);
		pcshape[size]->Set(x1, y1, x2, y2);
		pcshape[size]->Trail(hdc);
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		x2 = pt.x;
		y2 = pt.y;
		MoveToEx(hdc, x1, y1, NULL);
		pcshape[size]->Set(x1, y1, x2, y2);
		pcshape[size]->Trail(hdc);
		ReleaseDC(hWnd, hdc);
	}
}

/// <summary>
/// Do something, when paint is called
/// </summary>
/// <param name="hWnd"></param>
void MyEditor::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < size; i++)
	{
		if (pcshape[i]) pcshape[i]->Show(hdc);
	}
	EndPaint(hWnd, &ps);
}

/// <summary>
/// Change InitMenuPopup
/// </summary>
/// <param name="hWnd"></param>
/// <param name="wParams"></param>
void MyEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);

	if ((HMENU)wParams == hSubMenu)
	{
		for (auto& item : allMenus)
		{
			CheckMenuItem(hSubMenu, item, MF_UNCHECKED);
		}
		
		switch (pcshape[size]->InitMenuPopup())
		{
		case 0:
			CheckMenuItem(hSubMenu, IDM_POINT, MF_CHECKED);
			break;
		case 1:
			CheckMenuItem(hSubMenu, IDM_LINE, MF_CHECKED);
			break;
		case 2:
			CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_CHECKED);
			break;
		case 3:
			CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_CHECKED);
			break;
		case 4:
			CheckMenuItem(hSubMenu, IDM_LINEOO, MF_CHECKED);
			break;
		case 5:
			CheckMenuItem(hSubMenu, IDM_CUBE, MF_CHECKED);
			break;
		}
	}
}

#pragma endregion Functions
