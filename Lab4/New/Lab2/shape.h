#include "pch.h"

/// <summary>
/// Main class for shapes
/// </summary>
class Shape {
protected:
	long xs1, ys1, xs2, ys2;
public:
	~Shape();
	void Set(long, long, long, long);
	virtual void Show(HDC) = 0;
	virtual Shape* Copy() = 0;
	virtual void RubberTrack(HDC) = 0;
	virtual int InitMenuPopup() = 0;
};

class PointShape : public Shape
{
	void Show(HDC);
	virtual Shape* Copy();
	void RubberTrack(HDC);
	int InitMenuPopup();
};

class LineShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	virtual Shape* Copy();
	void RubberTrack(HDC);
	int InitMenuPopup();
};

class RectangleShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	virtual Shape* Copy();
	void RubberTrack(HDC);
	int InitMenuPopup();
};

class EllipseShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	virtual Shape* Copy();
	void RubberTrack(HDC);
	int InitMenuPopup();
};

class LineOOShape : public LineShape, public EllipseShape {
public:
	void Show(HDC);
	virtual Shape* Copy();
	void RubberTrack(HDC);
	int InitMenuPopup();
};

class CubeShape : public RectangleShape, public LineShape {
public:
	void Show(HDC);
	virtual Shape* Copy();
	void RubberTrack(HDC);
	int InitMenuPopup();
};