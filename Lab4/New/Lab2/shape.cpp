#include "framework.h"
#include "pch.h"
#include "shape.h"
#include "colors.h"

#pragma region Functions

Shape::~Shape() {};

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

/// <summary>
/// Shows the pixel
/// </summary>
/// <param name="hdc">handle to a device context</param>
void PointShape::Show(HDC hdc)
{
	SetPixel(hdc, xs1, ys1, black);
}

void PointShape::Trail(HDC hdc) {}

int PointShape::InitMenuPopup()
{
	return 0;
}

Shape* PointShape::Copy()
{
	return new PointShape();
}

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

void LineShape::Trail(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

int LineShape::InitMenuPopup()
{
	return 1;
}

Shape* LineShape::Copy()
{
	return new LineShape();
}

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

void RectangleShape::Trail(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs1, ys2);
	LineTo(hdc, xs2, ys2);
	LineTo(hdc, xs2, ys1);
	LineTo(hdc, xs1, ys1);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

int RectangleShape::InitMenuPopup()
{
	return 2;
}

Shape* RectangleShape::Copy()
{
	return new RectangleShape();
}

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

void EllipseShape::Trail(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	Ellipse(hdc, xs1, ys1, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

int EllipseShape::InitMenuPopup()
{
	return 3;
}

Shape* EllipseShape::Copy()
{
	return new EllipseShape();
}

void LineOOShape::Show(HDC hdc)
{
	long x1, x2, y1, y2;
	x1 = xs1;
	y1 = ys1;
	x2 = xs2;
	y2 = ys2;
	LineShape::Set(x1, y1, x2, y2);
	LineShape::Show(hdc);
	EllipseShape::Set(x1 + 10, y1 + 10, x1 - 10, y1 - 10);
	EllipseShape::Show(hdc);
	EllipseShape::Set(x2 + 10, y2 + 10, x2 - 10, y2 - 10);
	EllipseShape::Show(hdc);
	LineShape::Set(x1, y1, x2, y2);
}

void LineOOShape::Trail(HDC hdc)
{
	long x1, x2, y1, y2;
	x1 = xs1;
	y1 = ys1;
	x2 = xs2;
	y2 = ys2;
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	Ellipse(hdc, x1 + 10, y1 + 10, x1 - 10, y1 - 10);
	Ellipse(hdc, x2 + 10, y2 + 10, x2 - 10, y2 - 10);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

int LineOOShape::InitMenuPopup()
{
	return 4;
}

Shape* LineOOShape::Copy()
{
	return new LineOOShape();
}

void CubeShape::Show(HDC hdc)
{
	long x1, x2, y1, y2;
	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;
	RectangleShape::Set(x1 - 75, y1 - 75, x1 + 75, y1 + 75);
	RectangleShape::Show(hdc);
	RectangleShape::Set(x2 - 75, y2 - 75, x2 + 75, y2 + 75);
	RectangleShape::Show(hdc);
	LineShape::Set(x1 - 75, y1 - 75, x2 - 75, y2 - 75);
	LineShape::Show(hdc);
	LineShape::Set(x1 - 75, y1 + 75, x2 - 75, y2 + 75);
	LineShape::Show(hdc);
	LineShape::Set(x1 + 75, y1 + 75, x2 + 75, y2 + 75);
	LineShape::Show(hdc);
	LineShape::Set(x1 + 75, y1 - 75, x2 + 75, y2 - 75);
	LineShape::Show(hdc);
	LineShape::Set(x1, y1, x2, y2);
}

void CubeShape::Trail(HDC hdc)
{
	long x1, x2, y1, y2;
	x1 = xs1;
	y1 = ys1;
	x2 = xs2;
	y2 = ys2;
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, x1 - 75, y1 - 75, x1 + 75, y1 + 75);
	Rectangle(hdc, x2 - 75, y2 - 75, x2 + 75, y2 + 75);
	LineTo(hdc, x1, y1);
	MoveToEx(hdc, x1 - 75, y1 - 75, NULL);
	LineTo(hdc, x2 - 75, y2 - 75);
	MoveToEx(hdc, x1 - 75, y1 + 75, NULL);
	LineTo(hdc, x2 - 75, y2 + 75);
	MoveToEx(hdc, x1 + 75, y1 + 75, NULL);
	LineTo(hdc, x2 + 75, y2 + 75);
	MoveToEx(hdc, x1 + 75, y1 - 75, NULL);
	LineTo(hdc, x2 + 75, y2 - 75);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

int CubeShape::InitMenuPopup()
{
	return 5;
}

Shape* CubeShape::Copy()
{
	return new CubeShape();
}

#pragma endregion Functions
