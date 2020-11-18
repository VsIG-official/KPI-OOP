#include "framework.h"
#include "pch.h"
#include "my_table.h"
using namespace std;

char shapeName, shapeColor;
long XI1, YI1, XI2, YI2;

void MyTable::Add(HWND)
{	
	ofstream myfile;
	myfile.open("D://ForStudy/OOP/KPI-OOP/Lab5/objects.txt");
	myfile << "Writing this to a file.\n";
	myfile << "Writing this to a file.\n";
	myfile << "Writing this to a file.\n";
	myfile << "Writing this to a file.\n";
	//DialogBox(hInst, MAKEINTRESOURCE(IDD_TABLE), hWnd, About);
	myfile.close();
}
