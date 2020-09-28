#include "framework.h"
#include "pch.h"
#include "shape_editor.h"

#pragma region Variables

const int Size_Of_Array = 109;
Shape** pcshape = new Shape * [Size_Of_Array];
int size = 0;
bool isPressed;

#pragma endregion Variables

#pragma region Functions

#pragma region ShapeObjectsEditor

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
	if (pse) delete pse;
	pse = new PointEditor;
}

/// <summary>
/// Starts the LineEditor
/// </summary>
void ShapeObjectsEditor::StartLineEditor()
{
	if (pse) delete pse;
	pse = new LineEditor;
}

/// <summary>
/// Starts the RectangleEditor
/// </summary>
void ShapeObjectsEditor::StartRectangleEditor()
{
	if (pse) delete pse;
	pse = new RectangleEditor;
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

#pragma endregion ShapeObjectsEditor

#pragma region ShapeEditor

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
/// Do something on Mouse moving
/// </summary>
/// <param name="hWnd">window</param>
void ShapeEditor::OnMouseMove(HWND hWnd) {}

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
/// Do something on left mouse button clicked
/// </summary>
/// <param name="hWnd">window</param>
void PointEditor::OnLBdown(HWND hWnd)
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
void PointEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = FALSE;

	PointShape* Point = new PointShape;
	Point->Set(x1, y1, x2, y2);
	pcshape[size] = Point;
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
}

#pragma endregion PointEditor

#pragma region LineEditor

/// <summary>
/// Do something on left mouse button clicked
/// </summary>
/// <param name="hWnd">window</param>
void LineEditor::OnLBdown(HWND hWnd)
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
void LineEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = FALSE;

	LineShape* Line = new LineShape;
	Line->Set(x1, y1, x2, y2);
	pcshape[size] = Line;
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
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
	hPen = CreatePen(PS_SOLID, 1, red);
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
/// Do something on left mouse button clicked
/// </summary>
/// <param name="hWnd">window</param>
void RectangleEditor::OnLBdown(HWND hWnd)
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
void RectangleEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = FALSE;

	RectangleShape* Rectangle = new RectangleShape;
	Rectangle->Set(2 * x1 - x2, 2 * y1 - y2, x2, y2);
	pcshape[size] = Rectangle;
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
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
	hPen = CreatePen(PS_SOLID, 1, red);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, 2 * x1 - x2, 2 * y1 - y2, x2, y2);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	Rectangle(hdc, 2 * x1 - x2, 2 * y1 - y2, x2, y2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

#pragma endregion RectangleEditor

#pragma region EllipseEditor

/// <summary>
/// Do something on left mouse button clicked
/// </summary>
/// <param name="hWnd">window</param>
void EllipseEditor::OnLBdown(HWND hWnd)
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
void EllipseEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = FALSE;

	EllipseShape* Ellipse = new EllipseShape;
	Ellipse->Set(x1, y1, x2, y2);
	pcshape[size] = Ellipse;
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
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
	hPen = CreatePen(PS_SOLID, 1, red);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Ellipse(hdc, x1, y1, x2, y2);
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	Ellipse(hdc, x1, y1, x2, y2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

#pragma endregion EllipseEditor

#pragma endregion Functions
