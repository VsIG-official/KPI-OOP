#pragma once
#include "pch.h"
#include "editor.h"
#include "Resource.h"
#include "shape.h"

#pragma region Editors

/// <summary>
/// Shape editor class for figures
/// </summary>
class MyEditor {
public:
	//MyEditor() {};
	long x1, y1, x2, y2;
	~MyEditor();
	void Start(Shape*);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

#pragma endregion Editors
