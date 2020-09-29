#pragma once
#include "pch.h"
#include "editor.h"
#include "Resource.h"

#pragma region Editors

/// <summary>
/// Shape editor class for figures
/// </summary>
class ShapeEditor : public Editor
{
protected:
	long x1, x2, y1, y2;
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
};

/// <summary>
/// Shape editor class for figure objects
/// </summary>
class ShapeObjectsEditor
{
private:
	ShapeEditor* pse;
public:
	ShapeObjectsEditor(void);
	~ShapeObjectsEditor();
	void StartPointEditor();
	void StartLineEditor();
	void StartRectangleEditor();
	void StartEllipseEditor();
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
};

/// <summary>
/// Point editor class for points
/// </summary>
class PointEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
};

/// <summary>
/// Line editor class for lines
/// </summary>
class LineEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
};

/// <summary>
/// Rectangle editor class for rectangles
/// </summary>
class RectangleEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
};

/// <summary>
/// Ellipse editor class for ellipses
/// </summary>
class EllipseEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
};

#pragma endregion Editors
