#include "pch.h"

/// <summary>
/// Main class for shapes
/// </summary>
class Shape
{
protected:
	long XS1, YS1, XS2, YS2;
public:
	~Shape();
	void Set(long, long, long, long);
	virtual void Show(HDC) = 0;
	virtual Shape* Duplicate() = 0;
	virtual void Trail(HDC) = 0;
	virtual int InitMenuPopup() = 0;
};

/// <summary>
/// Class for point
/// </summary>
class PointShape : public Shape
{
	void Show(HDC);
	virtual Shape* Duplicate();
	void Trail(HDC);
	int InitMenuPopup();
};

/// <summary>
/// Class for line
/// </summary>
class LineShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	virtual Shape* Duplicate();
	void Trail(HDC);
	int InitMenuPopup();
};

/// <summary>
/// Class for rectangle
/// </summary>
class RectangleShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	virtual Shape* Duplicate();
	void Trail(HDC);
	int InitMenuPopup();
};

/// <summary>
/// Class for ellipse
/// </summary>
class EllipseShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	virtual Shape* Duplicate();
	void Trail(HDC);
	int InitMenuPopup();
};

/// <summary>
/// Class for lineOO
/// </summary>
class LineOOShape : public LineShape, public EllipseShape 
{
public:
	void Show(HDC);
	virtual Shape* Duplicate();
	void Trail(HDC);
	int InitMenuPopup();
};

/// <summary>
/// Class for cube
/// </summary>
class CubeShape : public RectangleShape, public LineShape 
{
public:
	void Show(HDC);
	virtual Shape* Duplicate();
	void Trail(HDC);
	int InitMenuPopup();
};
