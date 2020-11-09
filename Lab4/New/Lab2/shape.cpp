#include "framework.h"
#include "pch.h"
#include "shape.h"
#include "colors.h"
#include "toolbar.h"

#pragma region Variables

int lineOOInt = 20;
int cubeInt = 50;

#pragma endregion Variables

#pragma region Functions

/// <summary>
/// Get coords of points
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
/// Function for showing final shape
/// </summary>
/// <param name="hdc"></param>
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

/// <summary>
/// Function for copying
/// </summary>
/// <returns></returns>
Shape* PointShape::Copy()
{
	return new PointShape();
}

/// <summary>
/// Function for showing final shape
/// </summary>
/// <param name="hdc"></param>
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
	hPen = CreatePen(PS_DOT, 1, black);
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

/// <summary>
/// Function for copying
/// </summary>
/// <returns></returns>
Shape* LineShape::Copy()
{
	return new LineShape();
}

/// <summary>
/// Function for showing final shape
/// </summary>
/// <param name="hdc"></param>
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
	hPen = CreatePen(PS_DOT, 1, black);
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

/// <summary>
/// Function for copying
/// </summary>
/// <returns></returns>
Shape* RectangleShape::Copy()
{
	return new RectangleShape();
}

/// <summary>
/// Function for showing final shape
/// </summary>
/// <param name="hdc"></param>
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
	hPen = CreatePen(PS_DOT, 1, black);
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

/// <summary>
/// Function for copying
/// </summary>
/// <returns></returns>
Shape* EllipseShape::Copy()
{
	return new EllipseShape();
}

/// <summary>
/// Function for showing final shape
/// </summary>
/// <param name="hdc"></param>
void LineOOShape::Show(HDC hdc)
{
	long X1, X2, Y1, Y2;
	X1 = XS1;
	Y1 = YS1;
	X2 = XS2;
	Y2 = YS2;
	LineShape::Set(X1, Y1, X2, Y2);
	LineShape::Show(hdc);
	EllipseShape::Set(X1 + lineOOInt, Y1 + lineOOInt, 
		X1 - lineOOInt, Y1 - lineOOInt);
	EllipseShape::Show(hdc);
	EllipseShape::Set(X2 + lineOOInt, Y2 + lineOOInt,
		X2 - lineOOInt, Y2 - lineOOInt);
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
	hPen = CreatePen(PS_DOT, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, X1, Y1, NULL);
	LineTo(hdc, X2, Y2);
	Ellipse(hdc, X1 + lineOOInt, Y1 + lineOOInt,
		X1 - lineOOInt, Y1 - lineOOInt);
	Ellipse(hdc, X2 + lineOOInt, Y2 + lineOOInt,
		X2 - lineOOInt, Y2 - lineOOInt);
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

/// <summary>
/// Function for copying
/// </summary>
/// <returns></returns>
Shape* LineOOShape::Copy()
{
	return new LineOOShape();
}

/// <summary>
/// Function for showing final shape
/// </summary>
/// <param name="hdc"></param>
void CubeShape::Show(HDC hdc)
{
	long X1, X2, Y1, Y2;
	X1 = XS1; Y1 = YS1; X2 = XS2; Y2 = YS2;
	RectangleShape::Set(X1 - cubeInt, Y1 - cubeInt,
		X1 + cubeInt, Y1 + cubeInt);
	RectangleShape::Show(hdc);
	RectangleShape::Set(X2 - cubeInt, Y2 - cubeInt,
		X2 + cubeInt, Y2 + cubeInt);
	RectangleShape::Show(hdc);
	LineShape::Set(X1 - cubeInt, Y1 - cubeInt,
		X2 - cubeInt, Y2 - cubeInt);
	LineShape::Show(hdc);
	LineShape::Set(X1 - cubeInt, Y1 + cubeInt,
		X2 - cubeInt, Y2 + cubeInt);
	LineShape::Show(hdc);
	LineShape::Set(X1 + cubeInt, Y1 + cubeInt,
		X2 + cubeInt, Y2 + cubeInt);
	LineShape::Show(hdc);
	LineShape::Set(X1 + cubeInt, Y1 - cubeInt,
		X2 + cubeInt, Y2 - cubeInt);
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
	hPen = CreatePen(PS_DOT, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, X1 - cubeInt, Y1 - cubeInt,
		X1 + cubeInt, Y1 + cubeInt);
	Rectangle(hdc, X2 - cubeInt, Y2 - cubeInt,
		X2 + cubeInt, Y2 + cubeInt);
	LineTo(hdc, X1, Y1);
	MoveToEx(hdc, X1 - cubeInt, Y1 - cubeInt, NULL);
	LineTo(hdc, X2 - cubeInt, Y2 - cubeInt);
	MoveToEx(hdc, X1 - cubeInt, Y1 + cubeInt, NULL);
	LineTo(hdc, X2 - cubeInt, Y2 + cubeInt);
	MoveToEx(hdc, X1 + cubeInt, Y1 + cubeInt, NULL);
	LineTo(hdc, X2 + cubeInt, Y2 + cubeInt);
	MoveToEx(hdc, X1 + cubeInt, Y1 - cubeInt, NULL);
	LineTo(hdc, X2 + cubeInt, Y2 - cubeInt);
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

/// <summary>
/// Function for copying
/// </summary>
/// <returns></returns>
Shape* CubeShape::Copy()
{
	return new CubeShape();
}

Shape::~Shape() {};

#pragma endregion Functions
