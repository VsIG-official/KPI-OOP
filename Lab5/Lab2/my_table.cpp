#include "framework.h"
#include "pch.h"
#include "my_table.h"

char shapeName, shapeColor;
long XI1, YI1, XI2, YI2;

void MyTable::Add(HWND, std::string)
{
	FILE* fout;
	errno_t err;

	//fout = fopen("D://ForStudy/OOP/KPI-OOP/Lab5/objects.txt","wt");
	err = fopen_s(&fout, "D://ForStudy/OOP/KPI-OOP/Lab5/objects.txt", "wt");

	if (err)
	{
		fprintf((FILE*)err, "%s, %d, %d, %d, %d, %s\\n", 
			shapeName, XI1, YI1, XI2, YI2, shapeColor);
	}

	fclose((FILE*)err);
}
