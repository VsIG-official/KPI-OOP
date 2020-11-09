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
private:
	static MyEditor* instance;
	MyEditor() {};
	MyEditor(const MyEditor&);
public:
	static MyEditor* getInstance();
	int x1, y1, x2, y2;
	~MyEditor();
	void Start(Shape*);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

extern Shape** pcshape;
//extern int c;

#pragma endregion Editors
