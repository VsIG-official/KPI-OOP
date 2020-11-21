#include "framework.h"
#include "pch.h"
#include "my_table.h"
using namespace std;

static string path = "D://ForStudy/OOP/KPI-OOP/Lab5/objects.txt";

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
		//myTableFile.clear();
		myTableFile << shapeDetails << "\n";
	}

	myTableFile.close();

	SendDlgItemMessage(hWndDlg, IDC_LIST, LB_ADDSTRING,
		0, (LPARAM)shapeDetails.c_str());
}
