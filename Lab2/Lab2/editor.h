#pragma once
#include "pch.h"

//---”айл editor.h---
//оголошення класу

class Editor // Main class
{
public:
	virtual void OnLBdown(HWND) = 0;
	virtual void OnLBup(HWND) = 0;
	virtual void OnMouseMove(HWND) = 0;
	virtual void OnPaint(HWND) = 0;
};
