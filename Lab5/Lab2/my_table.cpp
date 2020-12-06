#include "framework.h"
#include "pch.h"
#include "my_table.h"

static string path = "./objects.txt";

void MyTable::Add(HWND hWndDlg, string shapeDetails)
{	
	ofstream myTableFile;
	myTableFile.open(path);

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
		0, (LPARAM)shapeDetails.c_str());
}
