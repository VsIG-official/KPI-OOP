#include "pch.h"

/// <summary>
/// Main class for shapes
/// </summary>
class Shape
{
protected:
	long XS1, YS1, XS2, YS2;
public:
	void Set(long X1, long Y1, long X2, long Y2);
	virtual void Show(HDC) = 0;
	virtual void Trail(HDC) = 0;
	virtual int InitMenuPopup() = 0;
	virtual Shape* Duplicate() = 0;
	~Shape();
};

/// <summary>
/// Class for point
/// </summary>
class PointShape : public Shape
{
	virtual void Show(HDC);
	void Trail(HDC);
	int InitMenuPopup();
	virtual Shape* Duplicate();
};

/// <summary>
/// Class for line
/// </summary>
class LineShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	void Trail(HDC);
	int InitMenuPopup();
	virtual Shape* Duplicate();
};

/// <summary>
/// Class for rectangle
/// </summary>
class RectangleShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	void Trail(HDC);
	int InitMenuPopup();
	virtual Shape* Duplicate();
};

/// <summary>
/// Class for ellipse
/// </summary>
class EllipseShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	void Trail(HDC);
	int InitMenuPopup();
	virtual Shape* Duplicate();
};

/// <summary>
/// Class for lineOO
/// </summary>
class LineOOShape : public LineShape, public EllipseShape 
{
public:
	void Show(HDC);
	void Trail(HDC);
	int InitMenuPopup();
	virtual Shape* Duplicate();
};

/// <summary>
/// Class for cube
/// </summary>
class CubeShape : public RectangleShape, public LineShape 
{
public:
	void Show(HDC);
	void Trail(HDC);
	int InitMenuPopup();
	virtual Shape* Duplicate();
};
