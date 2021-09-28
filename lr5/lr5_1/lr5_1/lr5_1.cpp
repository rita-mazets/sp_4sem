// lr5_1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lr5_1.h"

#define MAX_LOADSTRING 100
#define ID_checkDraw 3000
#define ID_GrpButtons1 3001
#define ID_GrpButtons2 3002
#define ID_radBatRed 3003
#define ID_radBatBlue 3004
#define ID_radBatGreen 3005
#define ID_radBatCicle 3006
#define ID_radBatRect 3007
#define ID_radBatStar 3008
#define ID_radBatRhombus 3009

HWND hWnd, checkDraw, GrpButtons1, GrpButtons2,radBatRed, radBatBlue, radBatGreen, radBatCicle, radBatRect, radBatStar, radBatRhombus;
UINT mes;
char buffer[4] = "000";
COPYDATASTRUCT cd;
HWND app2;

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
    LoadStringW(hInstance, IDC_LR51, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LR51));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LR51));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LR51);
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

   checkDraw = CreateWindowW(L"BUTTON", L"Draw", WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 10, 290, 100, 20, hWnd, (HMENU)ID_checkDraw, hInstance, NULL);

   GrpButtons1 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Color:", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 10, 10, 350, 100, hWnd, (HMENU)ID_GrpButtons1, hInst, NULL);
   radBatRed = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Red", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 30, 300, 20, hWnd, (HMENU)ID_radBatRed, hInst, NULL);
   radBatGreen = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Green", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 55, 300, 20, hWnd, (HMENU)ID_radBatGreen, hInst, NULL);
   radBatBlue = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Blue", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 80, 300, 20, hWnd, (HMENU)ID_radBatBlue, hInst, NULL);


   GrpButtons2 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Figure:", WS_VISIBLE | WS_CHILD | BS_GROUPBOX, 10, 150, 350, 125, hWnd, (HMENU)ID_GrpButtons1, hInst, NULL);
   radBatCicle = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Cicle", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 170, 300, 20, hWnd, (HMENU)ID_radBatCicle, hInst, NULL);
   radBatRect = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Rectangle", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 195, 300, 20, hWnd, (HMENU)ID_radBatRect, hInst, NULL);
   radBatStar = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Star", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 220, 300, 20, hWnd, (HMENU)ID_radBatStar, hInst, NULL);
   radBatRhombus = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Rhombus", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 245, 300, 20, hWnd, (HMENU)ID_radBatRhombus, hInst, NULL);

   mes = RegisterWindowMessageW(L"Lab10");

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void FillBuffer(int index, char value)
{
	buffer[index] = value;
	cd.lpData = &buffer;
	cd.cbData = sizeof(buffer);
	app2 = FindWindowW(NULL, L"Lab10_2");
	if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
	else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
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
	
	//COPYDATASTRUCT cd;
	//HWND app2;
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_checkDraw:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[0] = '1';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"lr5_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
				else if (chkState == BST_UNCHECKED)
				{
					buffer[0] = '0';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"lr5_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case ID_radBatRed:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[1] = '1';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"lr5_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case ID_radBatGreen:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[1] = '2';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"lr5_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case ID_radBatBlue:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[1] = '3';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"lr5_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case ID_radBatCicle:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[2] = '1';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"lr5_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case ID_radBatRect:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[2] = '2';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"lr5_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case ID_radBatStar:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[2] = '3';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"lr5_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
			break;
		case ID_radBatRhombus:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				LRESULT chkState = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
				if (chkState == BST_CHECKED)
				{
					buffer[2] = '4';
					cd.lpData = &buffer;
					cd.cbData = sizeof(buffer);
					app2 = FindWindowW(NULL, L"lr5_2");
					if (app2 == NULL) MessageBoxA(hWnd, "App not find!", "CheckBox", MB_OK);
					else SendMessageW(app2, WM_COPYDATA, 0, (LPARAM)&cd);
				}
			}
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
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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
