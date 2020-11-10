#pragma once
#include "pch.h"
#include "Resource.h"
#include "shape.h"

#pragma region Editors

/// <summary>
/// Shape editor class for figures
/// </summary>
class MyEditor {
public:
	void Start(Shape*);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
	~MyEditor();
	long X1, Y1, X2, Y2;
};

#pragma endregion Editors
