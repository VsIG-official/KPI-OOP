#include "framework.h"
#include "pch.h"
#include "my_table.h"

char shapeName, shapeColor;
long X1, Y1, X2, Y2;

void MyTable::Add(HWND, std::string)
{
	FILE* fout;
	fout = fopen("D://ForStudy/OOP/KPI-OOP/Lab5/objects.txt","wt");

	if (fout)
	{
		fprintf(fout, "%s, %d, %d, %d, %d, %s\\n", 
			shapeName, X1, Y1, X2, Y2, shapeColor);
	}

	fclose(fout);
}
