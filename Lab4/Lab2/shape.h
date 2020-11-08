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

class PointShape : public Shape
{
public:
	void Show(HDC hdc);
};

class LineShape : public virtual Shape
{
public:
	virtual void Show(HDC hdc);
};

class RectangleShape : public virtual Shape
{
public:
	virtual void Show(HDC hdc);
};

class EllipseShape : public virtual Shape
{
public:
	virtual void Show(HDC hdc);
};

class LineOOShape : public LineShape, public EllipseShape
{
public:
	virtual void Show(HDC hdc);
};

class CubeShape : public LineShape, public RectangleShape
{
public:
	virtual void Show(HDC hdc);
};

