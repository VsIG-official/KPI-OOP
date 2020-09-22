#pragma once
#include "pch.h"
#include "editor.h"

//---Файл shape_editor.h---

class ShapeEditor : public Editor {
protected:
    //корисні члени, які враховують специфіку Windows-програм
public:
    ShapeEditor(void);
    void OnLBdown(HWND);
    void OnLBup(HWND);
    void OnMouseMove(HWND);
    void OnPaint(HWND);
    void OnInitMenuPopup(HWND,WPARAM);      //додатковий інтерфейсний метод
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