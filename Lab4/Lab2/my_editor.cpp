#include "framework.h"
#include "pch.h"
#include "my_editor.h"
#include "shape.h"

#pragma region Variables

const int Size_Of_Array = 110;
Shape* pcshape[Size_Of_Array];
int size = 0;
bool isPressed;

#pragma endregion Variables

#pragma region Functions

#pragma region ShapeObjectsEditor

void MyEditor::Start(Shape* shape)
{
	//ID = id;
	//if (object) delete object;
	//object = shape;
};


/// <summary>
/// Constructor
/// </summary>
ShapeObjectsEditor::ShapeObjectsEditor()
{
	pse = new PointEditor;
}

/// <summary>
/// Destructor
/// </summary>
ShapeObjectsEditor::~ShapeObjectsEditor()
{
	for (int i = 0; i < size; i++)
	{
		delete pcshape[i];
	}
}

/// <summary>
/// Starts the PointEditor
/// </summary>
void ShapeObjectsEditor::StartPointEditor()
{
	if (pse)
	{
		delete pse;
	}
	pse = new PointEditor;
	SetShape(0);
}

/// <summary>
/// Starts the LineEditor
/// </summary>
void ShapeObjectsEditor::StartLineEditor()
{
	if (pse)
	{
		delete pse;
	}
	pse = new LineEditor;
	SetShape(1);
}

/// <summary>
/// Starts the RectangleEditor
/// </summary>
void ShapeObjectsEditor::StartRectangleEditor()
{
	if (pse)
	{
		delete pse;
	}
	pse = new RectangleEditor;
	SetShape(2);
}

/// <summary>
/// Starts the EllipseEditor
/// </summary>
void ShapeObjectsEditor::StartEllipseEditor()
{
	if (pse)
	{
		delete pse;
	}
	pse = new EllipseEditor;
	SetShape(3);
}

/// <summary>
/// Do something on left mouse button clicked
/// </summary>
/// <param name="hWnd">window</param>
void ShapeObjectsEditor::OnLBdown(HWND hWnd)
{
	if (pse)
	{
		pse->OnLBdown(hWnd);
	}
}

/// <summary>
/// Do something on left mouse button unclicked
/// </summary>
/// <param name="hWnd">window</param>
void ShapeObjectsEditor::OnLBup(HWND hWnd)
{
	if (pse)
	{
		pse->OnLBup(hWnd);
	}
}

/// <summary>
/// Do something on left mouse moving
/// </summary>
/// <param name="hWnd">window</param>
void ShapeObjectsEditor::OnMouseMove(HWND hWnd)
{
	if (pse && isPressed)
	{
		pse->OnMouseMove(hWnd);
	}
}

/// <summary>
/// Do something on paint
/// </summary>
/// <param name="hWnd">window</param>
void ShapeObjectsEditor::OnPaint(HWND hWnd)
{
	ShapeEditor* draw = new ShapeEditor;
	draw->OnPaint(hWnd);
}

/// <summary>
/// Sets the mark in figures menu
/// </summary>
/// <param name="hWnd"></param>
/// <param name="wParams"></param>
void ShapeObjectsEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams)
{
	if (pse)
	{
		pse->OnInitMenuPopup(hWnd, wParams);
	}
}

#pragma endregion ShapeObjectsEditor

#pragma region ShapeEditor

void ShapeEditor::OnMouseMove(HWND hWnd) {};

/// <summary>
/// Do something on left mouse button clicked
/// </summary>
/// <param name="hWnd">window</param>
void ShapeEditor::OnLBdown(HWND hWnd)
{
	isPressed = TRUE;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
}

/// <summary>
/// Do something on left mouse button unclicked
/// </summary>
/// <param name="hWnd">window</param>
void ShapeEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = FALSE;
}

/// <summary>
/// InitMenu Popup
/// </summary>
/// <param name="hWnd"></param>
/// <param name="wParams"></param>
void ShapeEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams) {};

/// <summary>
/// Do something on paint
/// </summary>
/// <param name="hWnd">window</param>
void ShapeEditor::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < size; i++)
	{
		if (pcshape[i])
		{
			pcshape[i]->Show(hdc);
		}
	}
	EndPaint(hWnd, &ps);
}

#pragma endregion ShapeEditor

#pragma region PointEditor

/// <summary>
/// Do something on left mouse button unclicked
/// </summary>
/// <param name="hWnd">window</param>
void PointEditor::OnLBup(HWND hWnd)
{
	__super::OnLBup(hWnd);
	PointShape* Point = new PointShape;
	Point->Set(x1, y1, x2, y2);
	pcshape[size] = Point;
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
}

/// <summary>
/// Sets the Check
/// </summary>
/// <param name="hWnd"></param>
/// <param name="wParams"></param>
void PointEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParams == hSubMenu)
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
	}
}

#pragma endregion PointEditor

#pragma region LineEditor

/// <summary>
/// Do something on left mouse button unclicked
/// </summary>
/// <param name="hWnd">window</param>
void LineEditor::OnLBup(HWND hWnd)
{
	__super::OnLBup(hWnd);
	LineShape* Line = new LineShape;
	Line->Set(x1, y1, x2, y2);
	pcshape[size] = Line;
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
}

/// <summary>
/// Sets the Check
/// </summary>
/// <param name="hWnd"></param>
/// <param name="wParams"></param>
void LineEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParams == hSubMenu)
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
	}
}

/// <summary>
/// Do something on Mouse moving
/// </summary>
/// <param name="hWnd">window</param>
void LineEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPen, hPenOld;
	HDC hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, blue);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

#pragma endregion LineEditor

#pragma region RectangleEditor

/// <summary>
/// Do something on left mouse button unclicked
/// </summary>
/// <param name="hWnd">window</param>
void RectangleEditor::OnLBup(HWND hWnd)
{
	__super::OnLBup(hWnd);
	RectangleShape* Rectangle = new RectangleShape;
	Rectangle->Set(x1, y1, x2, y2);
	pcshape[size] = Rectangle;
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
}

/// <summary>
/// Sets the Check
/// </summary>
/// <param name="hWnd"></param>
/// <param name="wParams"></param>
void RectangleEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParams == hSubMenu)
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
	}
}

/// <summary>
/// Do something on Mouse moving
/// </summary>
/// <param name="hWnd">window</param>
void RectangleEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPen, hPenOld;
	HDC hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, blue);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, x1, y1, x2, y2);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	Rectangle(hdc, x1, y1, x2, y2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

#pragma endregion RectangleEditor

#pragma region EllipseEditor

/// <summary>
/// Do something on left mouse button unclicked
/// </summary>
/// <param name="hWnd">window</param>
void EllipseEditor::OnLBup(HWND hWnd)
{
	__super::OnLBup(hWnd);
	EllipseShape* Ellipse = new EllipseShape;
	Ellipse->Set(2 * x1 - x2, 2 * y1 - y2, x2, y2);
	pcshape[size] = Ellipse;
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
}

/// <summary>
/// Sets the Check
/// </summary>
/// <param name="hWnd"></param>
/// <param name="wParams"></param>
void EllipseEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParams == hSubMenu)
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_CHECKED);
	}
}

/// <summary>
/// Do something on Mouse moving
/// </summary>
/// <param name="hWnd">window</param>
void EllipseEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPen, hPenOld;
	HDC hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, blue);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Arc(hdc, 2 * x1 - x2, 2 * y1 - y2, x2, y2, 0, 0, 0, 0);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	Arc(hdc, 2 * x1 - x2, 2 * y1 - y2, x2, y2, 0, 0, 0, 0);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

#pragma endregion EllipseEditor

#pragma endregion Functions
