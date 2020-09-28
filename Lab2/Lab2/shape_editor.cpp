#include "framework.h"
#include "pch.h"
#include "shape_editor.h"

// Variables
const int Size_Of_Array = 109;
Shape** pcshape = new Shape * [Size_Of_Array];
int size = 0;
bool isPressed;

// Constructor
ShapeObjectsEditor::ShapeObjectsEditor()
{
	pse = new PointEditor;
}

// Destructor
ShapeObjectsEditor::~ShapeObjectsEditor()
{
	for (int i = 0; i < size; i++)
	{
		delete pcshape[i];
	}
}

// ShapeObjectsEditor functions
void ShapeObjectsEditor::StartPointEditor()
{
	if (pse) delete pse;
	pse = new PointEditor;
}

void ShapeObjectsEditor::StartLineEditor()
{
	if (pse) delete pse;
	pse = new LineEditor;
}

void ShapeObjectsEditor::StartRectEditor()
{
	if (pse) delete pse;
	pse = new RectEditor;
}

void ShapeObjectsEditor::StartEllipseEditor()
{
	if (pse)
	{
		delete pse;
	}
	pse = new EllipseEditor;
}

void ShapeObjectsEditor::OnLBdown(HWND hWnd)
{
	if (pse)
	{
		pse->OnLBdown(hWnd);
	}
}

void ShapeObjectsEditor::OnLBup(HWND hWnd)
{
	if (pse)
	{
		pse->OnLBup(hWnd);
	}
}

void ShapeObjectsEditor::OnMouseMove(HWND hWnd)
{
	if (pse && isPressed)
	{
		pse->OnMouseMove(hWnd);
	}
}

void ShapeObjectsEditor::OnPaint(HWND hWnd)
{
	ShapeEditor* draw = new ShapeEditor;
	draw->OnPaint(hWnd);
}

// ShapeEditor Functions
void ShapeEditor::OnLBdown(HWND hWnd)
{
	isPressed = true;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
}

void ShapeEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = false;
}

void ShapeEditor::OnMouseMove(HWND hWnd) {}

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

// Point:
void PointEditor::OnLBdown(HWND hWnd)
{
	isPressed = true;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
}

void PointEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = false;

	PointShape* Point = new PointShape;
	Point->Set(x1, y1, x2, y2);
	pcshape[size] = Point;
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
}

// Line:
void LineEditor::OnLBdown(HWND hWnd)
{
	isPressed = true;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
}

void LineEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = false;

	LineShape* Line = new LineShape;
	Line->Set(x1, y1, x2, y2);
	pcshape[size] = Line;
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
}

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

// Rect:
void RectEditor::OnLBdown(HWND hWnd)
{
	isPressed = true;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
}

void RectEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = FALSE;

	RectShape* Rect = new RectShape;
	Rect->Set(2 * x1 - x2, 2 * y1 - y2, x2, y2);
	pcshape[size] = Rect;
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
}

void RectEditor::OnMouseMove(HWND hWnd)
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

// Ellipse:
void EllipseEditor::OnLBdown(HWND hWnd)
{
	isPressed = true;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
}

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
