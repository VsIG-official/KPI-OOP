#pragma once
#include "pch.h"

//---���� editor.h---
//���������� �����

class Editor
{
public:         //�, �������, �� ������� ���������� ����������?
	virtual void OnLBdown(HWND) = 0;
	virtual void OnLBup(HWND) = 0;
	virtual void OnMouseMove(HWND) = 0;
	virtual void OnPaint(HWND) = 0;
};
