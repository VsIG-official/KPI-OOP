#pragma once
#include "pch.h"
#include "Resource.h"
#include "shape.h"

#pragma region Editors

/// <summary>
/// Shape editor class for figures
/// </summary>
class MyEditor {
private:
	MyEditor() {};
	MyEditor(const MyEditor&);
	MyEditor& operator = (MyEditor&);
public:
	static MyEditor& getInstance()
	{
		static MyEditor instance;
		return instance;
	}
	void Start(Shape*);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
	~MyEditor();
	long X1, Y1, X2, Y2;
	std::string GetDetails();
	void SelectShape(INT);
};

#pragma endregion Editors
