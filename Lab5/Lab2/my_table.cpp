#include "framework.h"
#include "pch.h"
#include "my_table.h"

static string pathForShapes = "objects.txt";
static LPCSTR exceptionString = "Can't open a file or find a file";

/// <summary>
/// Add shape to table
/// </summary>
/// <param name="shapeDetails">name and coords</param>
void MyTable::Add(HWND hWndDlg, std::string shapeDetails)
{		
	ofstream myTableFile;

	myTableFile.open(pathForShapes, ofstream::app);

	if (myTableFile.is_open())
	{
		myTableFile << shapeDetails << endl;
	}
	else
	{
		throw new exception(exceptionString);
	}
	myTableFile.close();

	SendDlgItemMessage(hWndDlg, IDC_LIST, LB_ADDSTRING,
		0, (LPARAM)shapeDetails.c_str());
}
