#pragma once
#include "pch.h"
#include "editor.h"
#include "Resource.h"
#include "shape.h"

#pragma region Editors

/// <summary>
/// Shape editor class for figure objects
/// </summary>
class MyEditor
{
private:
public:
	~MyEditor();
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
	void Add(Shape* object);
	Shape* ReturnObject(int i);
	void Start(Shape* shape,int id);
};

#pragma endregion Editors
