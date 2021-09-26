// LR6-9.cpp: определяет точку входа для консольного приложения.
//


#include <windows.h>
#include <unordered_map>

const int FPS = 30;

int x, y, buttonID = 100, buttonStopID = 322, buttonContinueID = 132;
std::unordered_map<int, HWND> buttons;

bool isEmpty;

struct Moving
{
	const int dXperS = 60;
	const int dYperS = 60;

	int dX, dY;
	int prevX = 0, prevY = 0;
	bool is_stopped = false;
} moving;

struct Image
{
	int sizeX = 100, sizeY = 100;

	HBITMAP hBitmap;
	HDC hDC;

} image;

void DrawImage(HWND *hWnd, int &x, int &y)
{
	PAINTSTRUCT ps;
	HBITMAP hBitmap;
	BITMAP bm;
	HDC hDC;
	HDC hMemDC;

	hDC = BeginPaint(*hWnd, &ps);

	if (image.hDC == nullptr)
	{
		image.hDC = CreateCompatibleDC(hDC);
		image.hBitmap = (HBITMAP)LoadImage(NULL, TEXT("image.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}

	hMemDC = image.hDC;
	hBitmap = image.hBitmap;


	GetObject(hBitmap, sizeof(BITMAP), &bm);
	SelectObject(hMemDC, hBitmap);
	BitBlt(hDC, moving.prevX, moving.prevY, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, WHITENESS);

	if (!isEmpty)
		BitBlt(hDC, x, y, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, SRCCOPY);
	else
		BitBlt(hDC, moving.prevX + moving.dX, moving.prevY + moving.dY, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, WHITENESS);

	image.sizeX = bm.bmWidth + 15;
	image.sizeY = bm.bmHeight + 35;

	ReleaseDC(*hWnd, hDC);
	EndPaint(*hWnd, &ps);
}

inline void CheckCoordinates(HWND hWnd)
{
	RECT rect = { 0 };
	GetWindowRect(hWnd, &rect);

	int curX = x + rect.left,
		curY = y + rect.top;

	if (curX + image.sizeX >= rect.right)
		moving.dX = (-1) * abs(moving.dX);

	if (curX <= rect.left)
		moving.dX = abs(moving.dX);

	if (curY + image.sizeY >= rect.bottom)
		moving.dY = (-1) * abs(moving.dY);

	if (curY <= rect.top)
		moving.dY = abs(moving.dY);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ERASEBKGND:
	{
		break;
	}
	//реализация движения
	case WM_TIMER:
	{
		if (isEmpty)   break;

		CheckCoordinates(hWnd);
		moving.prevX = x;
		moving.prevY = y;
		if (!moving.is_stopped) {
			x += moving.dX;
			y += moving.dY;
		}
		InvalidateRect(hWnd, NULL, true);

		break;
	}
	case WM_COMMAND:
	{
		if (wParam == buttonID)
		{
			isEmpty = true;

			ShowWindow(buttons[buttonStopID], SW_HIDE);
			ShowWindow(buttons[buttonContinueID], SW_HIDE);

			InvalidateRect(hWnd, NULL, true);
			UpdateWindow(hWnd);
		}

		if (wParam == buttonStopID) {
			moving.is_stopped = true;
		}

		if (wParam == buttonContinueID) {
			moving.is_stopped = false;
		}

		break;
	}
	//отрисовка картинки при движении
	case WM_PAINT:
	{
		DrawImage(&hWnd, x, y);

		break;
	}
	case WM_LBUTTONUP:
	{
		if (!isEmpty)
			break;

		x = LOWORD(lParam) - image.sizeX / 2;
		y = HIWORD(lParam) - image.sizeY / 2;
		if (isEmpty) {
			ShowWindow(buttons[buttonStopID], SW_SHOW);
		}
		isEmpty = false;

		InvalidateRect(hWnd, NULL, true);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(NULL);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

ATOM RegNewWindow(HINSTANCE hInst, LPCSTR lClassName)
{
	WNDCLASS wcWndClass = { 0 };

	wcWndClass.hInstance = hInst;
	wcWndClass.lpfnWndProc = (WNDPROC)WndProc;
	wcWndClass.style = CS_HREDRAW | CS_VREDRAW;
	wcWndClass.lpszClassName = lClassName;
	wcWndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcWndClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
		
	return RegisterClass(&wcWndClass);
}

int WaitOne()
{
	MSG msg = { 0 };
	int iGetOk = 0;
	while ((iGetOk = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (iGetOk == -1) return 3;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

void SetFPS(HWND *hWnd)
{
	SetTimer(*hWnd, 228, 1000 / FPS, nullptr);

	moving.dX = moving.dXperS / FPS;
	moving.dY = moving.dYperS / FPS;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LPCTSTR lpzClass = TEXT("Window Class");

	RegNewWindow(hInst, lpzClass);

	HWND hWnd = CreateWindow(lpzClass, TEXT("Lab"),
		WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX, 100, 100, 700, 500, NULL, NULL,
		hInst, NULL);

	buttons[buttonID] = CreateWindow("BUTTON", "Clear",
		WS_VISIBLE | WS_CHILD, 5, 5, 105, 20, hWnd, (HMENU)buttonID,
		hInst, NULL);

	buttons[buttonStopID] = CreateWindow("BUTTON", "Stop",
		WS_VISIBLE | WS_CHILD, 5, 40, 105, 20, hWnd, (HMENU)buttonStopID,
		hInst, NULL);

	buttons[buttonContinueID] = CreateWindow("BUTTON", "Continue",
		WS_VISIBLE | WS_CHILD, 5, 75, 105, 20, hWnd, (HMENU)buttonContinueID,
		hInst, NULL);


	isEmpty = true;
	UpdateWindow(hWnd);
	SetFPS(&hWnd);

	return WaitOne();
}
