#include "framework.h"
#include "pch.h"
#include "shape.h"
#include "colors.h"

#pragma region Functions

/// <summary>
/// // Get coords of points
/// </summary>
/// <param name="x1">first point</param>
/// <param name="y1">second point</param>
/// <param name="x2">third point</param>
/// <param name="y2">fourth point</param>
void Shape::Set(long x1, long y1, long x2, long y2)
{
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
}

#pragma region Point

/// <summary>
/// Shows the pixel
/// </summary>
/// <param name="hdc">handle to a device context</param>
void PointShape::Show(HDC hdc)
{
	SetPixel(hdc, xs1, ys1, black);
}

void PointShape::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	int x = pt.x;
	int y = pt.y;
	this->Set(x, y, x, y);
	InvalidateRect(hWnd, NULL, TRUE);
}
Shape* PointShape::OnLBup(HWND hWnd)
{
	return 	new PointShape;
}

void PointShape::OnMouseMove(HWND hWnd) {};

#pragma endregion Point

#pragma region Line

/// <summary>
/// Shows the line
/// </summary>
/// <param name="hdc">handle to a device context</param>
void LineShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void LineShape::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xstart = pt.x;
	ystart = pt.y;
	start = TRUE;
	InvalidateRect(hWnd, NULL, TRUE);
}
void LineShape::OnMouseMove(HWND hWnd)
{
	if (start)
	{
		HDC hdc;
		HPEN hPenOld, hPen;
		POINT pt;
		hdc = GetDC(hWnd);
		SetROP2(hdc, R2_NOTXORPEN);
		hPen = CreatePen(PS_DASH, 1, RGB(255, 0, 0));
		hPenOld = (HPEN)SelectObject(hdc, hPen);
		if (xend, yend)
		{
			this->Set(xstart, ystart, xend, yend);
			this->Show(hdc);
		}
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		xend = pt.x;
		yend = pt.y;
		this->Set(xstart, ystart, xend, yend);
		this->Show(hdc);
		SelectObject(hdc, hPenOld);
		DeleteObject(hPen);
		ReleaseDC(hWnd, hdc);
	}
}
Shape* LineShape::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	start = FALSE;
	xstart = NULL;
	ystart = NULL;
	xend = NULL;
	yend = NULL;
	InvalidateRect(hWnd, NULL, TRUE);
	return new LineShape;
}


#pragma endregion Line

#pragma region Rectangle

/// <summary>
/// Shows the rectangle
/// </summary>
/// <param name="hdc">handle to a device context</param>
void RectangleShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	hBrush = CreateSolidBrush(white);
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	SelectObject(hdc, hBrush);
	Rectangle(hdc, xs1, ys1, xs2, ys2);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

#pragma endregion Rectangle

#pragma region Ellipse

/// <summary>
/// Shows the ellipse
/// </summary>
/// <param name="hdc">handle to a device context</param>
void EllipseShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Arc(hdc, xs1, ys1, xs2, ys2, 0, 0, 0, 0);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
};

#pragma endregion Ellipse

#pragma region LineOO

/// <summary>
/// Shows the ellipse
/// </summary>
/// <param name="hdc">handle to a device context</param>
void LineOOShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Arc(hdc, xs1, ys1, xs2, ys2, 0, 0, 0, 0);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
};

#pragma endregion LineOO

#pragma region Cube

/// <summary>
/// Shows the ellipse
/// </summary>
/// <param name="hdc">handle to a device context</param>
void CubeShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Arc(hdc, xs1, ys1, xs2, ys2, 0, 0, 0, 0);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
};

#pragma endregion Cube

Shape::~Shape() {};

#pragma endregion Functions
