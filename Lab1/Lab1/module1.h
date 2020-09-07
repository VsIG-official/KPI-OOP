//{{NO_DEPENDENCIES}}
// Included file created in Microsoft Visual C++.
// Using module1.rc
//
#define IDD_DIALOG1_MOD1                101
#define IDD_WORK_MOD1                   101
#define IDC_EDIT1                       1001
#define IDC_SCROLLBAR1                  1002
#define IDC_STATIC_MOD1                 1003

#pragma region VariablesAndFuntions

extern INT_PTR CALLBACK Work1_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

int Count(int pos);
extern char tempPlaceForText[];
extern int const maxSymbols;
extern int pos;
extern int numOfDig;
extern BOOL canWrite;

#pragma endregion

// Next default values for new objects
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        103
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1005
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
