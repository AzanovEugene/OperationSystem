// GoMessage.cpp : Определяет экспортированные функции для приложения DLL.
//

#include "GoMessage.h"
#include "resource.h"

WCHAR szStr[50];
BOOL CALLBACK DlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_COMMAND:
		switch (wParam) {
		case IDOK:
			GetDlgItemText(hwndDlg, IDC_EDIT1, szStr, 50);
			EndDialog(hwndDlg, IDOK);
			return true;
		}
	case IDCANCEL:
		EndDialog(hwndDlg, IDCANEL);
		return true;
	}

	return false;
}

void inMessage(HMODULE hLib, HWND hWnd, LPWSTR szStr1){
	DialogBox(hLib, MAKEINTRES(IDD_DIALOG2), hWnd, DlgProc);
	wcscpy_s(szZtr, szStr1);
	}