#include "framework.h"
#include "pch.h"
#include "shape.h"
#include "colors.h"
#include "toolbar.h"

#pragma region Variables

int lineOOInt = 20;
int cubeInt = 50;
long X1, X2, Y1, Y2;

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
/// Function for duplicating
/// </summary>
/// <returns></returns>
Shape* PointShape::Duplicate()
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
/// Function for duplicating
/// </summary>
/// <returns></returns>
Shape* LineShape::Duplicate()
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
/// Function for duplicating
/// </summary>
/// <returns></returns>
Shape* RectangleShape::Duplicate()
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
	Arc(hdc, 2 * XS1 - XS2, 2 * YS1 - YS2, XS2, YS2, 0, 0, 0, 0);
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
	Arc(hdc, 2 * XS1 - XS2, 2 * YS1 - YS2, XS2, YS2, 0, 0, 0, 0);

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
/// Function for duplicating
/// </summary>
/// <returns></returns>
Shape* EllipseShape::Duplicate()
{
	return new EllipseShape();
}

/// <summary>
/// Function for showing final shape
/// </summary>
/// <param name="hdc"></param>
void LineOOShape::Show(HDC hdc)
{
	X1 = XS1;
	Y1 = YS1;
	X2 = XS2;
	Y2 = YS2;
	LineShape::Set(X1, Y1, X2, Y2);
	LineShape::Show(hdc);
	EllipseShape::Set(X1, Y1, 
		X1 - lineOOInt, Y1 - lineOOInt);
	EllipseShape::Show(hdc);
	EllipseShape::Set(X2, Y2,
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
	X1 = XS1;
	Y1 = YS1;
	X2 = XS2;
	Y2 = YS2;
	LineShape::Set(X1, Y1, X2, Y2);
	LineShape::Trail(hdc);
	EllipseShape::Set(X1, Y1,
		X1 - lineOOInt, Y1 - lineOOInt);
	EllipseShape::Trail(hdc);
	EllipseShape::Set(X2, Y2,
		X2 - lineOOInt, Y2 - lineOOInt);
	EllipseShape::Trail(hdc);
	LineShape::Set(X1, Y1, X2, Y2);
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
/// Function for duplicating
/// </summary>
/// <returns></returns>
Shape* LineOOShape::Duplicate()
{
	return new LineOOShape();
}

/// <summary>
/// Function for showing final shape
/// </summary>
/// <param name="hdc"></param>
void CubeShape::Show(HDC hdc)
{
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
	X1 = XS1; Y1 = YS1; X2 = XS2; Y2 = YS2;
	RectangleShape::Set(X1 - cubeInt, Y1 - cubeInt,
		X1 + cubeInt, Y1 + cubeInt);
	RectangleShape::Trail(hdc);
	RectangleShape::Set(X2 - cubeInt, Y2 - cubeInt,
		X2 + cubeInt, Y2 + cubeInt);
	RectangleShape::Trail(hdc);
	LineShape::Set(X1 - cubeInt, Y1 - cubeInt,
		X2 - cubeInt, Y2 - cubeInt);
	LineShape::Trail(hdc);
	LineShape::Set(X1 - cubeInt, Y1 + cubeInt,
		X2 - cubeInt, Y2 + cubeInt);
	LineShape::Trail(hdc);
	LineShape::Set(X1 + cubeInt, Y1 + cubeInt,
		X2 + cubeInt, Y2 + cubeInt);
	LineShape::Trail(hdc);
	LineShape::Set(X1 + cubeInt, Y1 - cubeInt,
		X2 + cubeInt, Y2 - cubeInt);
	LineShape::Trail(hdc);
	LineShape::Set(X1, Y1, X2, Y2);
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
/// Function for duplicating
/// </summary>
/// <returns></returns>
Shape* CubeShape::Duplicate()
{
	return new CubeShape();
}

Shape::~Shape() {};

#pragma endregion Functions
