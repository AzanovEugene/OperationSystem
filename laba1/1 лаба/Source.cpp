#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "resource.h"
#include <tchar.h>

char szClassName[] = "LabOS-1";							//�������� ������ ����
char msg1[] = "�� ������� ���������������� �����";		//��������� 1
char msg2[] = "�� ������� ������� ��������� ����";		//��������� 2
char errMsg[] = "������";									//�������� ��������� ����
char wndName[] = "������������ ������ �1";				//������, ������������ � ��������� ����
TCHAR PName[] = _T("������������ ����");
TCHAR ChildName[] = _T("�������� ����");


LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);//������� ���� - ���������� DispatchMessage ��� ��������� ���������, ������������ ����
LRESULT CALLBACK	ChildProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

														//������� ������� ���������� �� Win32 API - �������, ������� ���������� ������ ��� ������� ����������
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	HWND hWnd;														//���������� ��� �������� ����������� ������������ ����
	WNDCLASS WndClass;												//��������� ������ ��� �������� ������� ������ ����
	MSG msg;														//��������� ������ ��� ������ � ���������� ������ ������� WinMain

																	//������������� ��������� ������, �������� �������� ������ ����
	WndClass.style = CS_HREDRAW | CS_VREDRAW;							//����, � ������� ��������� ����� ������ ���� (� ������ ������ ����� ����, ���������� Windows �������� ���� ��������� WM_PAINT ��� ��������� ��� ������� �� ��������� � �����������)
	WndClass.lpfnWndProc = WndProc;									//����, �������� ����� ������� ���� (������� ���� ������������ ���������, ������� �� ���������� ����)
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;									//���� � ������������ ����������, �������� ����������� ���� ����� ����
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));					//���� � ������������ ������ (������� LoadIcon ��������� ������ ������ �� ���������� Windows � ���������� ��� ����������)
	WndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));					//���� � ������������ ������� (������� LoadCursor ��������� ������ ������� �� ���������� Windows � ���������� ��� ����������)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);	//���� � ������������ ����� ��� ��������� ���� ������� ������� ���� (������� GetStockObject �������� ���������� ����������� ����� Windows � ��������������� LTGRAY_BRUSH)
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);										//���� � ��������� ����, �������������� � ���� (� ������ ������ ���� �����������)
	WndClass.lpszClassName = PName;						//���� � ���������� ��������� ������ ���� (����������� ���� ������� ���� � ���������� ��������� ����������)


	WNDCLASS WndClassChld;

	WndClassChld.style = CS_HREDRAW | CS_VREDRAW;
	WndClassChld.lpfnWndProc = ChildProc;
	WndClassChld.cbClsExtra = 0;
	WndClassChld.cbWndExtra = 0;
	WndClassChld.hInstance = hInstance;
	WndClassChld.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	WndClassChld.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	WndClassChld.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClassChld.lpszMenuName = MAKEINTRESOURCE(IDR_MENU2);
	WndClassChld.lpszClassName = ChildName;

	if (!RegisterClass(&WndClassChld)) {
		MessageBox(NULL, (LPCSTR)msg1, (LPCSTR)errMsg, MB_ICONERROR | MB_OK);			//������� ���������� ���� � ���������� �� ������ ����������� ������ ����
		return 0;													//��������� ������ ���������� ��-�� ������������� ��������� ����������� ��������� ����������
	}
																		//����������� ������ ���� � ������������ �������	
	if (!RegisterClass(&WndClass)) {
		MessageBox(NULL, (LPCSTR)msg1, (LPCSTR)errMsg, MB_ICONERROR | MB_OK);			//������� ���������� ���� � ���������� �� ������ ����������� ������ ����
		return 0;													//��������� ������ ���������� ��-�� ������������� ��������� ����������� ��������� ����������
	}

	//�������� ���������� ���� ��������� ������
	hWnd = CreateWindow(PName, _T("������������ ����"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	//���� ���� ������� �������, �� ��� ����������� ���������� �������� �� ����. � ������ ������� ���������� ���� ����� ����� ����
	if (!hWnd) {
		MessageBox(NULL, (LPCSTR)msg2, (LPCSTR)errMsg, MB_ICONERROR | MB_OK);			//������� ���������� ���� � ���������� �� ������ ��� �������� ���������� ����
		return 0;													//��������� ������ ���������� ��-�� ������������� ��������� ����������� ��������� ����������
	}

	ShowWindow(hWnd, SW_SHOWMAXIMIZED);										//���������� ����� ����������� ���������� ���� � ������������ hWnd
	UpdateWindow(hWnd);												//�������� ���� � ������������ hWnd ��������� WM_PAINT

																	// ���� ������� � ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0))	//GetMessage �������� ��������� �� ������� � �������� ��� � ��������� ���� TMSG. GetMessage ���������� ������� �������� ������ ��� ������� ��������� WM_QUIT
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);				//DispatchMessage - ��������� ���������; �� ����������� ���� � ��������� ���������� ����� ����, �������� ����� ������� ��������� ��������� � ��������� ��
	}

	return (int) msg.wParam;				//��������� ������ ���������� � ���������� ��� ��������� ������
}



//������� ���� - �������, ������� ������������ ���������, ���������� ���� ������������ �������� � ������� ������������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT r;

	switch (message)
	{
		//���� ��������� ��������� WM_PAINT - ������������ ������� ������� ����
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_40001:
			CreateWindow(ChildName, _T("�������� ����"), WS_VISIBLE, 10, 10, 500, 500, hWnd, 0, hInst, 0);
			break;
		case ID_40002:
			DestroyWindow(GetActiveWindow());
			break;
		case ID_40003:
			PostQuitMessage(0);
			break;
		case ID_40004://���������� ������������
			MessageBox(NULL, "�������� ������� �����������, ������ 1552�", "�����������", MB_ICONINFORMATION | MB_OK);
			break;
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);													//������� �������� ���� � ������������ hWnd
		GetClientRect(hWnd, &r);															//��������� ���������� �������� ������ � ������� ������� ����� ������� ������� ���� � ������������ hWnd � ���������� r
		DrawText(hdc, _T("������������ ����"), -1, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);	//������� ����� � �������, ������������ ����������� r, � ���� ��������� ������ �������������� �� ��������� � ����������� 
		EndPaint(hWnd, &ps);															//��������� ������ � ���������� ����
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);	//������� ������������ �������, ������� ������������ ��� ��������� ��������� �� ���������
	}
	return 0;
}

LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{   // ���������� ���������
	switch (message)
	{
		PAINTSTRUCT ps;
		HDC hdc;
		RECT r;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);													//������� �������� ���� � ������������ hWnd
		GetClientRect(hWnd, &r);															//��������� ���������� �������� ������ � ������� ������� ����� ������� ������� ���� � ������������ hWnd � ���������� r
		DrawText(hdc, ChildName, -1, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);	//������� ����� � �������, ������������ ����������� r, � ���� ��������� ������ �������������� �� ��������� � ����������� 
		EndPaint(hWnd, &ps);															//��������� ������ � ���������� ����
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_40005:
			DestroyWindow(GetForegroundWindow());
			break;
		case ID_40006:
			PostQuitMessage(0);
			break;
		}
		break;

	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}