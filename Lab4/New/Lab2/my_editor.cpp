#include "framework.h"
#include "pch.h"
#include "my_editor.h"
//#include "shape.h"

#pragma region Variables

const int Size_Of_Array = 110;
Shape* pcshape[Size_Of_Array];
int size = 0;
bool isPressed;

#pragma endregion Variables

#pragma region Functions

#pragma region ShapeObjectsEditor

MyEditor* MyEditor::instance = 0;

MyEditor* MyEditor::getInstance()
{
	if (!instance) instance = new MyEditor();
	return instance;
}

MyEditor::~MyEditor()
{
	for (int i = 0; i < size; i++) delete pcshape[i];
	delete pcshape;
}

void MyEditor::Start(Shape* shape)
{
	pcshape[size] = shape;
}

void MyEditor::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
	isPressed = true;
}

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

void MyEditor::OnMouseMove(HWND hWnd)
{
	if (isPressed)
	{
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
		//pcshape[size]->RubberTrack(hdc);
		ReleaseDC(hWnd, hdc);
	}
}

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

void MyEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParams == hSubMenu)
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINEOO, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_CUBE, MF_UNCHECKED);
		int smth = pcshape[size]->InitMenuPopup();
		switch (smth)
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
