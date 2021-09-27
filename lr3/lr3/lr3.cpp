// lr3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lr3.h"

#define MAX_LOADSTRING 100
#define BUTTON_CLEAR_ID 1
#define BUTTON_DRAW_ID 2

bool isVisible = false;

HWND hWnd, buttonClear, buttonDraw;

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
    LoadStringW(hInstance, IDC_LR3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LR3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LR3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LR3);
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

   buttonDraw = CreateWindow(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
       20, 20, 60, 60, hWnd, (HMENU)BUTTON_DRAW_ID, NULL, NULL);

   buttonClear = CreateWindow(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
       100, 20, 60, 60, hWnd, (HMENU)BUTTON_CLEAR_ID, NULL, NULL);

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
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case BUTTON_DRAW_ID:
			isVisible = true;
			InvalidateRect(hWnd, NULL, true);
			break;
		case BUTTON_CLEAR_ID:
			isVisible = false;
			InvalidateRect(hWnd, NULL, true);
			break;
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
	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT* draw = (DRAWITEMSTRUCT*)lParam;
		HBRUSH brush;
		HPEN pen;

		switch (draw->CtlID)
		{
		case BUTTON_DRAW_ID:
		{
			HDC hdc = draw->hDC;

			if (draw->itemAction == ODA_SELECT) {
				brush = CreateSolidBrush(RGB(0, 255, 255));
			}
			else {
				brush = CreateSolidBrush(RGB(255, 255, 0));
			}


			pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

			SelectObject(hdc, brush);
			SelectObject(hdc, pen);

			Rectangle(hdc, 0, 0, 60, 60);
			MoveToEx(hdc, 15, 30, NULL);
			LineTo(hdc, 30, 45);
			LineTo(hdc, 45, 15);
		}
		break;
		case BUTTON_CLEAR_ID:
		{
			HDC hdc = draw->hDC;

			if (draw->itemAction == ODA_SELECT) {
				brush = CreateSolidBrush(RGB(0, 0, 255));
			}
			else {
				brush = CreateSolidBrush(RGB(255, 0, 0));
			}
			pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

			SelectObject(hdc, brush);
			SelectObject(hdc, pen);

			Rectangle(hdc, 0, 0, 60, 60);
			MoveToEx(hdc, 20, 20, NULL);
			LineTo(hdc, 40, 40);
			MoveToEx(hdc, 40, 20, NULL);
			LineTo(hdc, 20, 40);
		}
		break;
		default:
			break;
		}
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		if (isVisible)
		{
			HBRUSH brush = CreateSolidBrush(RGB(12, 175, 7));
			SelectObject(hdc, brush);
			Rectangle(hdc, 0, 500, 2000, 1000);
			
			brush = CreateSolidBrush(RGB(233, 179, 79));
			SelectObject(hdc, brush);
			HPEN pen = CreatePen(BS_SOLID, 5, RGB(141, 104, 4));
			SelectObject(hdc, pen);
			Rectangle(hdc, 400, 300, 700, 600);

			brush = CreateSolidBrush(RGB(199, 78, 18));
			SelectObject(hdc, brush);
			pen = CreatePen(BS_SOLID, 5, RGB(179, 65, 8));
			SelectObject(hdc, pen);
			Rectangle(hdc, 350, 600, 750, 640);

			brush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, brush);
			Ellipse(hdc, 430, 400, 530, 500);
			MoveToEx(hdc, 480, 400, NULL);
			LineTo(hdc, 480, 500);
			MoveToEx(hdc, 430, 450, NULL);
			LineTo(hdc, 530, 450);

			brush = CreateSolidBrush(RGB(199, 78, 18));
			SelectObject(hdc, brush);
			POINT p1[4] = { 950, 450, 940, 700, 960, 700,950, 450};
			Polygon(hdc, p1, 4);
			POINT p2[4] = { 1160, 450, 1150, 600, 1170, 600,1160, 450 };
			Polygon(hdc, p2, 4);

			brush = CreateSolidBrush(RGB(199, 78, 18));
			SelectObject(hdc, brush);
			pen = CreatePen(BS_SOLID, 5, RGB(179, 65, 8));
			SelectObject(hdc, pen);
			POINT p[3] = { 330, 300, 550, 180, 770, 300,};
			Polygon(hdc, p, 3);
			Rectangle(hdc, 570, 380, 670, 600);

			brush = CreateSolidBrush(RGB(16, 137, 11));
			SelectObject(hdc, brush);
			pen = CreatePen(BS_SOLID, 3, RGB(0, 0, 0));
			SelectObject(hdc, pen);
			Ellipse(hdc, 900, 300, 1000, 500);
			Ellipse(hdc, 1100, 350, 1220, 520);

			brush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, brush);
			pen = CreatePen(BS_SOLID, 3, RGB(250, 250, 6));
			SelectObject(hdc, pen);
			Ellipse(hdc, 800, 10, 1000, 210);

			pen = CreatePen(BS_SOLID, 3, RGB(0, 0, 0));
			SelectObject(hdc, pen);
			Arc(hdc, 360, 30, 700, 290, 560, 30, 360, 0);
			Arc(hdc, 100, 290, 360, 30, 240, 30, 60, 0);
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
