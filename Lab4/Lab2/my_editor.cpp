#include "framework.h"
#include "pch.h"
#include "my_editor.h"
#include "toolbar.h"

#pragma region Variables

const int Size_Of_Array = 110;
Shape* pcshape[Size_Of_Array];
int size = 0;
bool isPressed;
int ID = 0;

#pragma endregion Variables

#pragma region Functions

Shape* object = NULL;

void MyEditor::Start(Shape* shape,int id)
{
	ID = id;
	if (object) delete object;
	object = shape;
};

//void MyEditor::Add(Shape* object)
//{
//	if (size < Size_Of_Array)
//	{
//		pcshape[size] = *&object;
//		size++;
//	}
//}

Shape* MyEditor::ReturnObject(int i)
{
	return pcshape[i];
}

/// <summary>
/// Destructor
/// </summary>
MyEditor::~MyEditor()
{
	delete pcshape;
}

void MyEditor::OnLBdown(HWND hWnd) {
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
	isPressed = true;
}

void MyEditor::OnLBup(HWND hWnd) {
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = false;
	pcshape[size]->Set(x1, y1, x2, y2);
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
}

void MyEditor::OnMouseMove(HWND hWnd) {
	if (isPressed) {
		POINT pt;
		HPEN hPen, hPenOld;
		HDC hdc = GetDC(hWnd);
		SetROP2(hdc, R2_NOTXORPEN);
		MoveToEx(hdc, x1, y1, NULL);
		pcshape[size]->Set(x1, y1, x2, y2);
		//pcshape[size]->RubberTrack(hdc);
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		x2 = pt.x;
		y2 = pt.y;
		MoveToEx(hdc, x1, y1, NULL);
		pcshape[size]->Set(x1, y1, x2, y2);
		//pcshape[c]->RubberTrack(hdc);
		ReleaseDC(hWnd, hdc);
	}
}

void MyEditor::OnPaint(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < size; i++) {
		if (pcshape[i]) pcshape[i]->Show(hdc);
	}
	EndPaint(hWnd, &ps);
}

/// <summary>
/// Sets the mark in figures menu
/// </summary>
/// <param name="hWnd"></param>
/// <param name="wParams"></param>
void MyEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	const int allTools = 6;
	int tools[allTools] = { ID_TOOL_POINT, ID_TOOL_LINE, ID_TOOL_RECTANGLE,
		ID_TOOL_ELLIPSE, ID_TOOL_LINEOO, ID_TOOL_CUBE };
	if ((HMENU)wParam == hSubMenu)
	{
		for (int i = 0; i < sizeof(tools); i++)
		{
			CheckMenuItem(hSubMenu, tools[i], MF_UNCHECKED);
		}
	}
	CheckMenuItem(hSubMenu, ID, MF_CHECKED);
}

#pragma endregion Functions
