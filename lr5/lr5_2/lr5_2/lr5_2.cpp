// lr5_2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lr5_2.h"

#include <string.h>

#define MAX_LOADSTRING 100

UINT mes;
int xgl = 0;
int ygl = 0;
char buffer[4] = "000";




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
    LoadStringW(hInstance, IDC_LR52, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LR52));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LR52));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LR52);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   mes = RegisterWindowMessageW(L"lr5_1");

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

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
	PAINTSTRUCT ps;
	HDC hdc;

	HBRUSH hBrush;                              
	hBrush = CreateSolidBrush(RGB(255, 255, 255)); 
	switch (message)
	{
	case WM_COPYDATA:
		strcpy_s(buffer, (char*)((PCOPYDATASTRUCT)lParam)->lpData);
		break;
	case WM_LBUTTONDOWN:
		xgl = LOWORD(lParam);
		ygl = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, FALSE); 
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
		int x, y;
		x = xgl;
		y = ygl;
		hdc = BeginPaint(hWnd, &ps);

		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		if (strchr(buffer, '0') != NULL)
		{
			break;
		}
		else
		{
			GetClientRect(hWnd, &Rect);
			HBRUSH hBrush1;                                 //создаём объект-кисть
			hBrush1 = CreateSolidBrush(RGB(255, 255, 255)); //задаём сплошную кисть, закрашенную цветом RGB
			FillRect(hdc, &Rect, hBrush1);
			DeleteObject(hBrush1);
			if (buffer[1] == '1')                                //красный
			{
				hBrush = CreateSolidBrush(RGB(255, 0, 0));
				SelectObject(hdc, hBrush);
			}
			else if (buffer[1] == '3')                                //синий
			{
				hBrush = CreateSolidBrush(RGB(0, 0, 255));
				SelectObject(hdc, hBrush);
			}
			else if (buffer[1] == '2')                                //зелёный
			{
				hBrush = CreateSolidBrush(RGB(0, 255, 0));
				SelectObject(hdc, hBrush);
			}


			if (buffer[2] == '4')                               //ромб
			{
				POINT poly[4];
				poly[0].x = x;
				poly[0].y = y - 50;
				poly[1].x = x + 50;
				poly[1].y = y;
				poly[2].x = x;
				poly[2].y = y + 50;
				poly[3].x = x - 50;
				poly[3].y = y;
				Polygon(hdc, poly, 4);
			}
			else if (buffer[2] == '2')                               //квадрат
			{
				POINT poly[4];
				poly[0].x = x - 70;
				poly[0].y = y - 70;
				poly[1].x = x + 70;
				poly[1].y = y - 70;
				poly[2].x = x + 70;
				poly[2].y = y + 70;
				poly[3].x = x - 70;
				poly[3].y = y + 70;
				Polygon(hdc, poly, 4);
			}
			else if (buffer[2] == '1')                               //круг
			{
				Ellipse(hdc, x - 70, y - 70, x + 70, y + 70);
			}
			else if (buffer[2] == '3')                               //звезда
			{
				POINT poly[10];
				poly[0].x = x - 50;
				poly[0].y = y - 68;
				poly[1].x = x - 30;
				poly[1].y = y - 10;
				poly[2].x = x - 80;
				poly[2].y = y + 26;
				poly[3].x = x - 18;
				poly[3].y = y + 26;
				poly[4].x = x;
				poly[4].y = y + 80;
				poly[5].x = x + 18;
				poly[5].y = y + 26;
				poly[6].x = x + 80;
				poly[6].y = y + 26;
				poly[7].x = x + 30;
				poly[7].y = y - 10;
				poly[8].x = x + 50;
				poly[8].y = y - 68;
				poly[9].x = x;
				poly[9].y = y - 32;
				Polygon(hdc, poly, 10);
			}
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
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
