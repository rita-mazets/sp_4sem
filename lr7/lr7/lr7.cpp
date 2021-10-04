﻿// lr7.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lr7.h"
#include <cmath>
#include <minwinbase.h>

#define MAX_LOADSTRING 100

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
    LoadStringW(hInstance, IDC_LR7, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LR7));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LR7));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LR7);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
#define START_BUTTON 1001
#define STOP_BUTTON 1002

int winWidth = 10;
int winHeight = 100;

HANDLE thread1, thread2;

struct ThreadArgs {
    int time;
    int x, y;
} p1, p2;

DWORD WINAPI MoveObject(ThreadArgs* args) {
    while (true) {
        args->time -= 10;
        if (args->time < 0)
            args->time += winWidth;
        args->x = args->time;
        args->y = 100;
        Sleep(70);
    }
    return 0;
}

bool active = false;

#define THREADCOUNT 2 

HANDLE ghWriteEvent;
HANDLE ghThreads[THREADCOUNT];

DWORD WINAPI FirstThreadMove(LPVOID);
DWORD WINAPI SecondThreadMove(LPVOID);


void InitThreadsnEvent(void)
{
    int i;
    DWORD dwThreadID;

    ghWriteEvent = CreateEvent(
        NULL,
        TRUE,
        FALSE,
        TEXT("WriteEvent")
    );

    if (ghWriteEvent == NULL)
    {
        return;
    }

    ghThreads[0] = CreateThread(
        NULL,
        0,
        FirstThreadMove,
        NULL,
        0,
        &dwThreadID);

    ghThreads[1] = CreateThread(
        NULL,
        0,
        SecondThreadMove,
        NULL,
        0,
        &dwThreadID);

    if (ghThreads[0] == NULL)
    {
        return;
    }
}
int X = 500;
int Y = 110;
CRITICAL_SECTION CriticalSection;

DWORD WINAPI FirstThreadMove(LPVOID lpParam)
{
    while (true) {
        EnterCriticalSection(&CriticalSection);
        X = (X + 5) % winHeight;
        LeaveCriticalSection(&CriticalSection);
        Sleep(1);
    }
    return 1;
}

DWORD WINAPI SecondThreadMove(LPVOID lpParam)
{
    while (true) {
        EnterCriticalSection(&CriticalSection);
        X = (X + 5) % winHeight;
        LeaveCriticalSection(&CriticalSection);
        Sleep(1);
    }
    return 1;
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
    HWND hWnd;

    hInst = hInstance; // Store instance handle in our global variable

    hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 1200, 400, NULL, NULL, hInstance, NULL);

    CreateWindow(L"BUTTON", L"Start", WS_CHILD | WS_VISIBLE,
        20, 10, 100, 30, hWnd, (HMENU)START_BUTTON, hInstance, NULL);
    CreateWindow(L"BUTTON", L"Stop", WS_CHILD | WS_VISIBLE,
        120, 10, 130, 30, hWnd, (HMENU)STOP_BUTTON, hInstance, NULL);

    p1.time = 0;
    p2.time = 100;

    thread1 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)MoveObject, &p1, 0, NULL);
    SuspendThread(thread1);

    thread2 = CreateThread(NULL, 0u, (LPTHREAD_START_ROUTINE)MoveObject, &p2, 0, NULL);
    SuspendThread(thread2);

    if (!InitializeCriticalSectionAndSpinCount(&CriticalSection,
        0x00000400))
        return 1;
    InitThreadsnEvent();
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
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        switch (wmId)
        {
        case START_BUTTON:
            if (!active) {
                ResumeThread(thread1);
                ResumeThread(thread2);

                SetTimer(hWnd, NULL, 20, NULL);

                active = true;
            }
            break;
        case STOP_BUTTON:
            if (active) {
                SuspendThread(thread1);
                SuspendThread(thread2);
                active = false;
            }
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
        break;
    case WM_TIMER:
        InvalidateRect(hWnd, NULL, true);
        if (active)
            SetTimer(hWnd, NULL, 20, NULL);
        break;
    case WM_SIZE:
        winWidth = LOWORD(lParam);
        winHeight = HIWORD(lParam);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        if (p1.y != 0)
        {
            HBRUSH brush;

            brush = CreateSolidBrush(RGB(16, 0, 55));
            SelectObject(hdc, brush);
            Rectangle(hdc, p1.x + 7, Y - 25, p1.x + 20, Y);
            Rectangle(hdc, p1.x, Y, p1.x + 100, Y + 40);
            Ellipse(hdc, p1.x, Y + 40, p1.x + 10, Y + 50);
            Ellipse(hdc, p1.x + 30, Y + 40, p1.x + 40, Y + 50);
            Ellipse(hdc, p1.x + 60, Y + 40, p1.x + 70, Y + 50);
            Ellipse(hdc, p1.x + 90, Y + 40, p1.x + 100, Y + 50);
        }
        EndPaint(hWnd, &ps);
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
