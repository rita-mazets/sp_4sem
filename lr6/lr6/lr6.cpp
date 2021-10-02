// lr6.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lr6.h"
#include "math.h"

#define MAX_LOADSTRING 100
#define ID_BUTTON_START 1
#define ID_BUTTON_STOP 2

HWND hWnd, button_spart, button_stop;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LR6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LR6));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LR6));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LR6);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   button_spart = CreateWindowW(L"BUTTON", L"Start", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 10, 10, 100, 50, hWnd, (HMENU)ID_BUTTON_START, hInstance, NULL);
   button_stop = CreateWindowW(L"BUTTON", L"Stop", BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_TABSTOP, 150, 10, 100, 50, hWnd, (HMENU)ID_BUTTON_STOP, hInstance, NULL);


   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

double alpha1 = 0, alpha2 = 0, alpha3 = 0;
DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	for (;;)
	{
		if ((int)lpParam == 1)
		{
			alpha1 += 1;
		}
		else if ((int)lpParam == 2)
		{
			alpha2 += 2;
		}
		else
		{
			alpha3 += 3;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		Sleep(50);
	}
	return 0;
}
HANDLE hThread1, hThread2, hThread3;

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	DWORD dwThreadId1, dwThreadId2, dwThreadId3;
	int param1 = 1;
	int param2 = 2;
	int param3 = 3;
	switch (message)
	{
	case WM_CREATE:
		hThread1 = CreateThread(NULL, 0, ThreadFunc, (LPVOID)param1, 0, &dwThreadId1);
		hThread2 = CreateThread(NULL, 0, ThreadFunc, (LPVOID)param2, 0, &dwThreadId2);
		//hThread3 = CreateThread(NULL, 0, ThreadFunc, (LPVOID)param3, 0, &dwThreadId3);
		//атрибуты без-ти, размер стека, функция, аргумент функции,флажки создания, идентификатор потока
		if (hThread1 == NULL) MessageBoxW(NULL, L"Cannot create first thread", L"Fail", MB_OK);
		if (hThread2 == NULL) MessageBoxW(NULL, L"Cannot create second thread", L"Fail", MB_OK);
		SuspendThread(hThread1);
		SuspendThread(hThread2);
		//SuspendThread(hThread3);

		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_BUTTON_START:             //Start
			ResumeThread(hThread1);
			ResumeThread(hThread2);
			ResumeThread(hThread3);
			break;
		case ID_BUTTON_STOP:                      //Stop
			SuspendThread(hThread1);
			SuspendThread(hThread2);
			SuspendThread(hThread3);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		RECT Rect;
		GetClientRect(hWnd, &Rect);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HBRUSH hBrush;                                 //создаём объект-кисть
		hBrush = CreateSolidBrush(RGB(255, 255, 255)); //задаём сплошную кисть, закрашенную цветом RGB
		FillRect(hdc, &Rect, hBrush);
		HPEN hPen1;                                    //Объявляется черную кисть
		hPen1 = CreatePen(1, 4, RGB(255, 0, 0));
		SelectObject(hdc, hPen1);

		MoveToEx(hdc, 100, 100 + alpha1, NULL);     //1 палочка
		LineTo(hdc, 100, 200 + alpha1);

		hPen1 = CreatePen(1, 4, RGB(0, 255, 0));
		SelectObject(hdc, hPen1);
		MoveToEx(hdc, 300, 100 + alpha2, NULL);     //2 палочка
		LineTo(hdc, 300, 200 + alpha2);

		/*hPen1 = CreatePen(1, 4, RGB(0, 0, 255));
		SelectObject(hdc, hPen1);
		MoveToEx(hdc, 500, 100 + alpha3, NULL);     //3 палочка
		LineTo(hdc, 500, 200 + alpha3);
		EndPaint(hWnd, &ps);*/
	}
	break;
	case WM_DESTROY:
		CloseHandle(hThread1);
		CloseHandle(hThread2);
		//CloseHandle(hThread3);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
