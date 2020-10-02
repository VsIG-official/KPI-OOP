#include "pch.h"

/// <summary>
/// Main class for shapes
/// </summary>
class Shape
{
protected:
	long xs1, ys1, xs2, ys2;
public:
	void Set(long x1, long y1, long x2, long y2);
	virtual void Show(HDC) = 0;
};

/// <summary>
/// Class for points
/// </summary>
class PointShape : public Shape
{
public:
	void Show(HDC);
};

/// <summary>
/// Class for lines
/// </summary>
class LineShape : public Shape
{
public:
	void Show(HDC);
};

/// <summary>
/// Class for rectangles
/// </summary>
class RectangleShape : public Shape
{
public:
	void Show(HDC);
};

/// <summary>
/// Class for ellipses
/// </summary>
class EllipseShape : public Shape
{
public:
	void Show(HDC);
};
