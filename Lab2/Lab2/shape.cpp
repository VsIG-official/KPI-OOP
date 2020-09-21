//---���� shape.h---
#include "pch.h"

static void StartPointEditor();

//---���������� �����---
class Shape
{
protected:
	long xs1, ys1, xs2, ys2;
public:
	void Set(long x1, long y1, long x2, long y2);
	virtual void Show(HDC) = 0;
	ShapeObjectsEditor(void);
	~ShapeObjectsEditor();
	void StartPointEditor();
	void StartLineEditor();
	void StartRectEditor();
	void StartEllipseEditor();
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);   //�������� ������� ��������
};

//---���������� ������ Set---
void Shape::Set(long x1, long y1, long x2, long y2)
{
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
}

void Shape::SetColor(COLORREF newColor)
{
	color = newColor;
}

void Shape::SetFill(BOOL isF)
{
	isFill = isF;
}

void PointShape::Show(HDC hdc)
{
	SetPixel(hdc, xs1, ys1, color);
}

void LineShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;

	hPen = CreatePen(PS_SOLID, 1, color);
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void RectShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;

	hPen = CreatePen(PS_SOLID, 1, color);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	if (isFill)
	{
		hBrush = CreateSolidBrush(color);
		hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
		SelectObject(hdc, hBrush);
		Rectangle(hdc, xs1, ys1, xs2, ys2);
		SelectObject(hdc, hBrushOld);
		DeleteObject(hBrush);
	}
	else
	{
		MoveToEx(hdc, xs1, ys1, NULL);
		LineTo(hdc, xs1, ys2);
		LineTo(hdc, xs2, ys2);
		LineTo(hdc, xs2, ys1);
		LineTo(hdc, xs1, ys1);
	}

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void EllipseShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;

	hPen = CreatePen(PS_SOLID, 1, color);
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	if (isFill)
	{
		hBrush = CreateSolidBrush(color);
		hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
		SelectObject(hdc, hBrush);
		Ellipse(hdc, xs1, ys1, xs2, ys2);
		SelectObject(hdc, hBrushOld);
		DeleteObject(hBrush);
	}
	else
	{
		Arc(hdc, xs1, ys1, xs2, ys2, 0, 0, 0, 0);
	}

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
};

