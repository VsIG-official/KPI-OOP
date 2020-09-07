//{{NO_DEPENDENCIES}}
// Included file created in Microsoft Visual C++.
// Using module1.rc
//

#ifndef MODULE_1_H
#define MODULE_1_H

#define IDD_DIALOG1_MOD1                101
#define IDD_WORK_MOD1                   101
#define IDC_EDIT1                       1001
#define IDC_SCROLLBAR1                  1002
#define IDC_STATIC_MOD1                 1003

#pragma region VariablesAndFuntions

extern INT_PTR CALLBACK Work1_MOD1(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
void OnInit_MOD1(HWND hDlg);
void OnLineLeft_MOD1(HWND hDlg);
void OnLineRight_MOD1(HWND hDlg);
void OnOkMod2_MOD1(HWND hDlg);
void OnThumbPosAndTrack_MOD1(HWND hDlg, WPARAM wParam);

int Count_MOD1(int pos_MOD1);
extern char tempPlaceForText_MOD1[];
extern int const maxSymbols_MOD1;
extern int pos_MOD1;
extern int numOfDig_MOD1;
extern BOOL canWrite_MOD1;

#pragma endregion

#endif // MODULE_1_H

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
