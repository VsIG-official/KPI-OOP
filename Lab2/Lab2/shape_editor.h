#pragma once
#include "pch.h"
#include "editor.h"

//---���� shape_editor.h---

class ShapeObjectsEditor
{
private:
    ShapeEditor* pse;
public:
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

class ShapeEditor : public Editor {
protected:
    long x1, y1, x2, y2;
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