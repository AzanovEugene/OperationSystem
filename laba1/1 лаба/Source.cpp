#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "resource.h"
#include <tchar.h>

char szClassName[] = "LabOS-1";							//Название класса окон
char msg1[] = "Не удалось зарегистрировать класс";		//Сообщение 1
char msg2[] = "Не удалось создать экземпляр окна";		//Сообщение 2
char errMsg[] = "Ошибка";									//Название диалового окна
char wndName[] = "Лабораторная работа №1";				//Строка, отображаемая в заголовке окна
TCHAR PName[] = _T("Родительское окно");
TCHAR ChildName[] = _T("Дочернее окно");


LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);//Функция окна - вызывается DispatchMessage для обработки сообщений, отправленных окну
LRESULT CALLBACK	ChildProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

														//Главная функция приложения на Win32 API - функция, которая вызывается первой при запуске приложения
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	HWND hWnd;														//Переменная для хранения дескриптора создаваемого окна
	WNDCLASS WndClass;												//Структура данных для описания свойств класса окон
	MSG msg;														//Структура данных для работы с сообщением внутри функции WinMain

																	//Инициализация структуры данных, хранящей свойства класса окон
	WndClass.style = CS_HREDRAW | CS_VREDRAW;							//Поле, в котором определен стиль класса окон (В данном случае стиль окон, заставляет Windows посылять окну сообщение WM_PAINT при изменении его размера по вертикали и горизонтали)
	WndClass.lpfnWndProc = WndProc;									//Поле, хранящее адрес функции окна (Функция окна обрабатывает сообщения, которые ОС направляет окну)
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;									//Поле с дескриптором приложения, которому принадлежит этот класс окон
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));					//Поле с дескриптором значка (Функция LoadIcon загружает ресурс значка из библиотеки Windows и возвращает его дескриптор)
	WndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));					//Поле с дескриптором курсора (Функция LoadCursor загружает ресурс лурсора из библиотеки Windows и возвращает его дескриптор)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);	//Поле с дескриптором кисти для рисования фона рабочей области окна (Функция GetStockObject получает дескриптор стандартной кисти Windows с идентификатором LTGRAY_BRUSH)
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);										//Поле с названием меню, прикрепленного к окну (В данном случае меню отсутствует)
	WndClass.lpszClassName = PName;						//Поле с уникальным названием класса окон (Регистрация двух классов окон с одинаковым названием невозможна)


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
		MessageBox(NULL, (LPCSTR)msg1, (LPCSTR)errMsg, MB_ICONERROR | MB_OK);			//Выводит диалоговое окно с сообщением об ощибке регистрации класса окон
		return 0;													//Завершает работу приложения из-за невозможности построить графический интерфейс приложения
	}
																		//Регистрация класса окон в операционной системе	
	if (!RegisterClass(&WndClass)) {
		MessageBox(NULL, (LPCSTR)msg1, (LPCSTR)errMsg, MB_ICONERROR | MB_OK);			//Выводит диалоговое окно с сообщением об ощибке регистрации класса окон
		return 0;													//Завершает работу приложения из-за невозможности построить графический интерфейс приложения
	}

	//Создание экземпляра окна заданного класса
	hWnd = CreateWindow(PName, _T("Родительское окно"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	//Если окно создано успешно, то ему назначается дескриптор отличный от нуля. В случае неудачи дескриптор окна будет равен нулю
	if (!hWnd) {
		MessageBox(NULL, (LPCSTR)msg2, (LPCSTR)errMsg, MB_ICONERROR | MB_OK);			//Выводит диалоговое окно с сообщением об ощибке при создании экземпляра окна
		return 0;													//Завершает работу приложения из-за невозможности построить графический интерфейс приложения
	}

	ShowWindow(hWnd, SW_SHOWMAXIMIZED);										//Определяет стиль отображения экземпляра окна с дескриптором hWnd
	UpdateWindow(hWnd);												//Посылает окну с дескриптором hWnd сообщение WM_PAINT

																	// Цикл выборки и обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))	//GetMessage выбирает сообщение из очереди и помещает его в структуру типа TMSG. GetMessage возвращает нулевое значение только при выборке сообщения WM_QUIT
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);				//DispatchMessage - диспетчер сообщений; по дескриптору окна в сообщении определяет класс окон, получает адрес функции обработки сообщений и запускает ее
	}

	return (int) msg.wParam;				//Завершает работу приложения и возвращает код окончания работы
}



//Функция окна - функция, которая обрабатывает сообщения, посылаемые окну операционной системой и другими приложениями
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT r;

	switch (message)
	{
		//Блок обработки сообщения WM_PAINT - перерисовать рабочую область окна
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_40001:
			CreateWindow(ChildName, _T("Дочернее окно"), WS_VISIBLE, 10, 10, 500, 500, hWnd, 0, hInst, 0);
			break;
		case ID_40002:
			DestroyWindow(GetActiveWindow());
			break;
		case ID_40003:
			PostQuitMessage(0);
			break;
		case ID_40004://Информация разработчика
			MessageBox(NULL, "Сошников Евгений Геннадьевич, Группа 1552б", "Разработчик", MB_ICONINFORMATION | MB_OK);
			break;
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);													//Создает контекст окна с дескриптором hWnd
		GetClientRect(hWnd, &r);															//Сохраняет координаты верхнего левого и нижнего правого углов рабочей области окна с дескриптором hWnd в переменной r
		DrawText(hdc, _T("Родительское окно"), -1, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);	//Выводит текст в области, ограниченной параметрами r, в виде одиночной строки центрированной по вертикали и горизонтали 
		EndPaint(hWnd, &ps);															//Завершает работу с контекстом окна
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);	//Функция операционной системы, которая обрабатывает все остальные сообщения по умолчанию
	}
	return 0;
}

LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{   // Обработчик сообщений
	switch (message)
	{
		PAINTSTRUCT ps;
		HDC hdc;
		RECT r;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);													//Создает контекст окна с дескриптором hWnd
		GetClientRect(hWnd, &r);															//Сохраняет координаты верхнего левого и нижнего правого углов рабочей области окна с дескриптором hWnd в переменной r
		DrawText(hdc, ChildName, -1, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);	//Выводит текст в области, ограниченной параметрами r, в виде одиночной строки центрированной по вертикали и горизонтали 
		EndPaint(hWnd, &ps);															//Завершает работу с контекстом окна
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