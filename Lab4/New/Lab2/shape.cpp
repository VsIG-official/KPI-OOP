#include "framework.h"
#include "pch.h"
#include "shape.h"
#include "colors.h"
#include "toolbar.h"

#pragma region Functions

/// <summary>
/// // Get coords of points
/// </summary>
/// <param name="X1">first point</param>
/// <param name="Y1">second point</param>
/// <param name="X2">third point</param>
/// <param name="Y2">fourth point</param>
void Shape::Set(long X1, long Y1, long X2, long Y2)
{
	XS1 = X1;
	YS1 = Y1;
	XS2 = X2;
	YS2 = Y2;
}

/// <summary>
/// Shows the pixel
/// </summary>
/// <param name="hdc">handle to a device context</param>
void PointShape::Show(HDC hdc)
{
	SetPixel(hdc, XS1, YS1, black);
}

/// <summary>
/// Trail for point
/// </summary>
/// <param name="hdc"></param>
void PointShape::Trail(HDC hdc) {}

/// <summary>
/// Function to get id for Menu
/// </summary>
/// <returns></returns>
int PointShape::InitMenuPopup()
{
	return ID_TOOL_POINT;
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
	MoveToEx(hdc, XS1, YS1, NULL);
	LineTo(hdc, XS2, YS2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

/// <summary>
/// Trail for line
/// </summary>
/// <param name="hdc"></param>
void LineShape::Trail(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, XS1, YS1, NULL);
	LineTo(hdc, XS2, YS2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

/// <summary>
/// Function to get id for Menu
/// </summary>
/// <returns></returns>
int LineShape::InitMenuPopup()
{
	return ID_TOOL_LINE;
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
	Rectangle(hdc, XS1, YS1, XS2, YS2);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

/// <summary>
/// Trail for rectangle
/// </summary>
/// <param name="hdc"></param>
void RectangleShape::Trail(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, XS1, YS1, NULL);
	LineTo(hdc, XS1, YS2);
	LineTo(hdc, XS2, YS2);
	LineTo(hdc, XS2, YS1);
	LineTo(hdc, XS1, YS1);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

/// <summary>
/// Function to get id for Menu
/// </summary>
/// <returns></returns>
int RectangleShape::InitMenuPopup()
{
	return ID_TOOL_RECTANGLE;
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
	Arc(hdc, XS1, YS1, XS2, YS2, 0, 0, 0, 0);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
};

/// <summary>
/// Trail for ellipse
/// </summary>
/// <param name="hdc"></param>
void EllipseShape::Trail(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, XS1, YS1, NULL);
	Ellipse(hdc, XS1, YS1, XS2, YS2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

/// <summary>
/// Function to get id for Menu
/// </summary>
/// <returns></returns>
int EllipseShape::InitMenuPopup()
{
	return ID_TOOL_ELLIPSE;
}

Shape* EllipseShape::Copy()
{
	return new EllipseShape();
}

void LineOOShape::Show(HDC hdc)
{
	long X1, X2, Y1, Y2;
	X1 = XS1;
	Y1 = YS1;
	X2 = XS2;
	Y2 = YS2;
	LineShape::Set(X1, Y1, X2, Y2);
	LineShape::Show(hdc);
	EllipseShape::Set(X1 + 10, Y1 + 10, X1 - 10, Y1 - 10);
	EllipseShape::Show(hdc);
	EllipseShape::Set(X2 + 10, Y2 + 10, X2 - 10, Y2 - 10);
	EllipseShape::Show(hdc);
	LineShape::Set(X1, Y1, X2, Y2);
}

/// <summary>
/// Trail for lineOO
/// </summary>
/// <param name="hdc"></param>
void LineOOShape::Trail(HDC hdc)
{
	long X1, X2, Y1, Y2;
	X1 = XS1;
	Y1 = YS1;
	X2 = XS2;
	Y2 = YS2;
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, X1, Y1, NULL);
	LineTo(hdc, X2, Y2);
	Ellipse(hdc, X1 + 10, Y1 + 10, X1 - 10, Y1 - 10);
	Ellipse(hdc, X2 + 10, Y2 + 10, X2 - 10, Y2 - 10);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

/// <summary>
/// Function to get id for Menu
/// </summary>
/// <returns></returns>
int LineOOShape::InitMenuPopup()
{
	return ID_TOOL_LINEOO;
}

Shape* LineOOShape::Copy()
{
	return new LineOOShape();
}

void CubeShape::Show(HDC hdc)
{
	long X1, X2, Y1, Y2;
	X1 = XS1; Y1 = YS1; X2 = XS2; Y2 = YS2;
	RectangleShape::Set(X1 - 75, Y1 - 75, X1 + 75, Y1 + 75);
	RectangleShape::Show(hdc);
	RectangleShape::Set(X2 - 75, Y2 - 75, X2 + 75, Y2 + 75);
	RectangleShape::Show(hdc);
	LineShape::Set(X1 - 75, Y1 - 75, X2 - 75, Y2 - 75);
	LineShape::Show(hdc);
	LineShape::Set(X1 - 75, Y1 + 75, X2 - 75, Y2 + 75);
	LineShape::Show(hdc);
	LineShape::Set(X1 + 75, Y1 + 75, X2 + 75, Y2 + 75);
	LineShape::Show(hdc);
	LineShape::Set(X1 + 75, Y1 - 75, X2 + 75, Y2 - 75);
	LineShape::Show(hdc);
	LineShape::Set(X1, Y1, X2, Y2);
}

/// <summary>
/// Trail for cube
/// </summary>
/// <param name="hdc"></param>
void CubeShape::Trail(HDC hdc)
{
	long X1, X2, Y1, Y2;
	X1 = XS1;
	Y1 = YS1;
	X2 = XS2;
	Y2 = YS2;
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, X1 - 75, Y1 - 75, X1 + 75, Y1 + 75);
	Rectangle(hdc, X2 - 75, Y2 - 75, X2 + 75, Y2 + 75);
	LineTo(hdc, X1, Y1);
	MoveToEx(hdc, X1 - 75, Y1 - 75, NULL);
	LineTo(hdc, X2 - 75, Y2 - 75);
	MoveToEx(hdc, X1 - 75, Y1 + 75, NULL);
	LineTo(hdc, X2 - 75, Y2 + 75);
	MoveToEx(hdc, X1 + 75, Y1 + 75, NULL);
	LineTo(hdc, X2 + 75, Y2 + 75);
	MoveToEx(hdc, X1 + 75, Y1 - 75, NULL);
	LineTo(hdc, X2 + 75, Y2 - 75);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

/// <summary>
/// Function to get id for Menu
/// </summary>
/// <returns></returns>
int CubeShape::InitMenuPopup()
{
	return ID_TOOL_CUBE;
}

Shape* CubeShape::Copy()
{
	return new CubeShape();
}

Shape::~Shape() {};

#pragma endregion Functions
