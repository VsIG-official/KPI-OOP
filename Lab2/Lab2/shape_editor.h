#pragma once
#include "pch.h"
#include "editor.h"

//---���� shape_editor.h---

class ShapeEditor : public Editor {
protected:
    //������ �����, �� ���������� ��������� Windows-�������
public:
    ShapeEditor(void);
    void OnLBdown(HWND);
    void OnLBup(HWND);
    void OnMouseMove(HWND);
    void OnPaint(HWND);
    void OnInitMenuPopup(HWND,WPARAM);      //���������� ������������ �����
};

class PointEditor : public ShapeEditor
{

};

class LineEditor : public ShapeEditor
{

};

class RectEditor : public ShapeEditor
{

};

class EllipseEditor : public ShapeEditor
{

};