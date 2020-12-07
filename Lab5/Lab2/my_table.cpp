#include "framework.h"
#include "pch.h"
#include "my_table.h"

static string name = "objects.txt";

/// <summary>
/// Add shape to table
/// </summary>
/// <param name="shapeDetails">name and coords</param>
void MyTable::Add(HWND hWndDlg, wchar_t* shapeDetails[1024])
{	
	ofstream myTableFile(name);

	if (!myTableFile.is_open())
	{
		throw new exception("Can't open a file");
	}
	else
	{
		myTableFile << shapeDetails << "\n";
	}

	myTableFile.close();

	SendDlgItemMessage(hWndDlg, IDC_LIST, LB_ADDSTRING,
		0, (LPARAM)shapeDetails);
}
