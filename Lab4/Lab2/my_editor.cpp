#include "framework.h"
#include "pch.h"
#include "my_editor.h"
#include "toolbar.h"

#pragma region Variables

const int Size_Of_Array = 110;
Shape* pcshape[Size_Of_Array];
int size = 0;
bool isPressed;
int ID = 0;

#pragma endregion Variables

#pragma region Functions

Shape* object = NULL;

void MyEditor::Start(Shape* shape,int id)
{
	ID = id;
	if (object) delete object;
	object = shape;
};

void MyEditor::Add(Shape* object)
{
	if (size < Size_Of_Array)
	{
		pcshape[size] = *&object;
		size++;
	}
}

Shape* MyEditor::ReturnObject(int i)
{
	return pcshape[i];
}

/// <summary>
/// Destructor
/// </summary>
MyEditor::~MyEditor()
{
	delete pcshape;
}

/// <summary>
/// Do something on left mouse button clicked
/// </summary>
/// <param name="hWnd">window</param>
void MyEditor::OnLBdown(HWND hWnd)
{
	if (object)
	{
		object->OnLBdown(hWnd);
	}
}

/// <summary>
/// Do something on left mouse button unclicked
/// </summary>
/// <param name="hWnd">window</param>
void MyEditor::OnLBup(HWND hWnd)
{
	Add(*&object);
	if (object)
		object = object->OnLBup(hWnd);
};

/// <summary>
/// Do something on left mouse moving
/// </summary>
/// <param name="hWnd">window</param>
void MyEditor::OnMouseMove(HWND hWnd)
{
	if (object) object->OnMouseMove(hWnd);
};

/// <summary>
/// Do something on paint
/// </summary>
/// <param name="hWnd">window</param>
void MyEditor::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < Size_Of_Array; i++)
		if (i < size)
			ReturnObject(i)->Show(hdc);
	EndPaint(hWnd, &ps);
	ReleaseDC(hWnd, hdc);
};

/// <summary>
/// Sets the mark in figures menu
/// </summary>
/// <param name="hWnd"></param>
/// <param name="wParams"></param>
void MyEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	const int allTools = 6;
	int tools[allTools] = { ID_TOOL_POINT, ID_TOOL_LINE, ID_TOOL_RECTANGLE,
		ID_TOOL_ELLIPSE, ID_TOOL_LINEOO, ID_TOOL_CUBE };
	if ((HMENU)wParam == hSubMenu)
	{
		for (int i = 0; i < sizeof(tools); i++)
		{
			CheckMenuItem(hSubMenu, tools[i], MF_UNCHECKED);
		}
	}
	CheckMenuItem(hSubMenu, ID, MF_CHECKED);
}

#pragma endregion Functions
