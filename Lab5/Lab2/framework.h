#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows
#define APSTUDIO_HIDDEN_SYMBOLS
#include <windows.h>
#include "prsht.h"
#undef APSTUDIO_HIDDEN_SYMBOLS
// Файлы заголовков среды выполнения C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <fstream>
//--підключення бібліотеки Common Control Library--
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "Shlwapi.lib")
