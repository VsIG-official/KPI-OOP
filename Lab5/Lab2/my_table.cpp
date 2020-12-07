#include "framework.h"
#include "pch.h"
#include "my_table.h"

static string name = "objects.txt";
static LPCSTR exceptionString = "Can't open a file or find a file";
INT countForShapes = 0;

/// <summary>
/// Add shape to table
/// </summary>
/// <param name="shapeDetails">name and coords</param>
void MyTable::Add(HWND hWndDlg, std::string shapeDetails)
{	
	
	ofstream myTableFile;
	if (countForShapes == 0)
	{
		myTableFile.open(name, std::ofstream::out | std::ofstream::trunc);
		myTableFile.close();
	}

	myTableFile.open(name, ofstream::app);

	if (myTableFile.is_open())
	{

		myTableFile << shapeDetails << endl;
	}
	else
	{
		throw new exception(exceptionString);
	}
	myTableFile.close();

	countForShapes++;

	SendDlgItemMessage(hWndDlg, IDC_LIST, LB_ADDSTRING,
		0, (LPARAM)shapeDetails.c_str());
}
