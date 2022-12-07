#define _CRT_SECURE_NO_WARNINGS
#define CELL_SIZE 70
#include <Windows.h>
#include <xstring>
#include <cstdlib>
#include <tchar.h>
#include <commdlg.h>
#include <commctrl.h>
#include <fstream>
#include <vector>
#include <string>
#include "resource.h"
//TBBUTTON tbb[] = {
//{STD_FILENEW, ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON,0,0,0,0},
//{STD_FILEOPEN, ID_FILE_OPEN,TBSTATE_ENABLED, TBSTYLE_BUTTON,0,0,0,0},
//{STD_FILESAVE, ID_FILE_SAVE,TBSTATE_ENABLED, TBSTYLE_BUTTON,0,0,0,0}
//};
//HINSTANCE hInst;

const int LineHeight = 16;//Высота строки текста + межстрочное расстояние

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");
int WINAPI WinMain(HINSTANCE This, // Дескриптор текущего приложения
	HINSTANCE Prev, // В современных системах всегда 0
	LPSTR cmd, // Командная строка
	int mode) // Режим отображения окна
{
	HWND hWnd; // Дескриптор главного окна программы
	MSG msg; // Структура для хранения сообщения
	WNDCLASS wc; // Класс окна
	// Определение класса окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; // Имя класса окна
	wc.lpfnWndProc = WndProc; // Функция окна
	wc.style = CS_HREDRAW | CS_VREDRAW; // Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Стандартный курсор
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); // Нет меню
	wc.cbClsExtra = 0; // Нет дополнительных данных класса
	wc.cbWndExtra = 0; // Нет дополнительных данных окна
	// Заполнение окна белым цветом
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0; // Регистрация класса окна 
	// Создание окна
	hWnd = CreateWindow(WinName, // Имя класса окна
		_T("Window Name"), // Заголовок окна
		WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, // Стиль окна
		CW_USEDEFAULT,// x
		CW_USEDEFAULT,// y Размеры окна
		CW_USEDEFAULT,// Width
		CW_USEDEFAULT,// Height
		HWND_DESKTOP, // Дескриптор родительского окна
		NULL, // Нет меню
		This, // Дескриптор приложения
		NULL); // Дополнительной информации нет
	ShowWindow(hWnd, mode); //Показать окно
	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);// Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg); // Посылает сообщение функции WndProc()
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	//HBRUSH darkBrush = CreateSolidBrush(RGB(158, 66, 29));
	//HBRUSH lightBrush = CreateSolidBrush(RGB(238, 199, 124));

	const wchar_t* pos[] = {
		L"A1", L"A2", L"A3", L"A4", L"A5", L"A6", L"A7", L"A8",
		L"B1", L"B2", L"B3", L"B4", L"B5", L"B6", L"B7", L"B8",
		L"C1", L"C2", L"C3", L"C4", L"C5", L"C6", L"C7", L"C8",
		L"D1", L"D2", L"D3", L"D4", L"D5", L"D6", L"D7", L"D8",
		L"E1", L"E2", L"E3", L"E4", L"E5", L"E6", L"E7", L"E8",
		L"F1", L"F2", L"F3", L"F4", L"F5", L"F6", L"F7", L"F8",
		L"G1", L"G2", L"G3", L"G4", L"G5", L"G6", L"G7", L"G8",
		L"H1", L"H2", L"H3", L"H4", L"H5", L"H6", L"H7", L"H8"
	};
	static int sx, sy;
	int x_left = 0, y_left = 0, x_right = CELL_SIZE, y_right = CELL_SIZE, count = 2, mouse_x, mouse_y;
	switch (message) {
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_LBUTTONDOWN:
		mouse_x = LOWORD(lParam);
		mouse_y = HIWORD(lParam);
		if (mouse_x > 560 || mouse_y > 560)
			MessageBox(hWnd, L"Out of board", L"Message", NULL);
		else {
			if (mouse_y < 70) {
				if (mouse_x < 70) {
					MessageBox(hWnd, pos[0], L"Message", NULL);
				}
				else if (mouse_x > 70 && mouse_x < 140) {
					MessageBox(hWnd, pos[1], L"Message", NULL);
				}
				else if (mouse_x > 140 && mouse_x < 210) {
					MessageBox(hWnd, pos[2], L"Message", NULL);
				}
				else if (mouse_x > 210 && mouse_x < 280) {
					MessageBox(hWnd, pos[3], L"Message", NULL);
				}
				else if (mouse_x > 280 && mouse_x < 350) {
					MessageBox(hWnd, pos[4], L"Message", NULL);
				}
				else if (mouse_x > 350 && mouse_x < 420) {
					MessageBox(hWnd, pos[5], L"Message", NULL);
				}
				else if (mouse_x > 420 && mouse_x < 490) {
					MessageBox(hWnd, pos[6], L"Message", NULL);
				}
				else if (mouse_x > 490 && mouse_x < 590) {
					MessageBox(hWnd, pos[7], L"Message", NULL);
				}
			}
			else if (mouse_y > 70 && mouse_y < 140) {
				if (mouse_x < 70) {
					MessageBox(hWnd, pos[8], L"Message", NULL);
				}
				else if (mouse_x > 70 && mouse_x < 140) {
					MessageBox(hWnd, pos[9], L"Message", NULL);
				}
				else if (mouse_x > 140 && mouse_x < 210) {
					MessageBox(hWnd, pos[10], L"Message", NULL);
				}
				else if (mouse_x > 210 && mouse_x < 280) {
					MessageBox(hWnd, pos[11], L"Message", NULL);
				}
				else if (mouse_x > 280 && mouse_x < 350) {
					MessageBox(hWnd, pos[12], L"Message", NULL);
				}
				else if (mouse_x > 350 && mouse_x < 420) {
					MessageBox(hWnd, pos[13], L"Message", NULL);
				}
				else if (mouse_x > 420 && mouse_x < 490) {
					MessageBox(hWnd, pos[14], L"Message", NULL);
				}
				else if (mouse_x > 490 && mouse_x < 590) {
					MessageBox(hWnd, pos[15], L"Message", NULL);
				}
			}
			else if (mouse_y > 140 && mouse_y < 210) {
				if (mouse_x < 70) {
					MessageBox(hWnd, pos[16], L"Message", NULL);
				}
				else if (mouse_x > 70 && mouse_x < 140) {
					MessageBox(hWnd, pos[17], L"Message", NULL);
				}
				else if (mouse_x > 140 && mouse_x < 210) {
					MessageBox(hWnd, pos[18], L"Message", NULL);
				}
				else if (mouse_x > 210 && mouse_x < 280) {
					MessageBox(hWnd, pos[19], L"Message", NULL);
				}
				else if (mouse_x > 280 && mouse_x < 350) {
					MessageBox(hWnd, pos[20], L"Message", NULL);
				}
				else if (mouse_x > 350 && mouse_x < 420) {
					MessageBox(hWnd, pos[21], L"Message", NULL);
				}
				else if (mouse_x > 420 && mouse_x < 490) {
					MessageBox(hWnd, pos[22], L"Message", NULL);
				}
				else if (mouse_x > 490 && mouse_x < 590) {
					MessageBox(hWnd, pos[23], L"Message", NULL);
				}
			}
			else if (mouse_y > 210 && mouse_y < 280) {
				if (mouse_x < 70) {
					MessageBox(hWnd, pos[24], L"Message", NULL);
				}
				else if (mouse_x > 70 && mouse_x < 140) {
					MessageBox(hWnd, pos[25], L"Message", NULL);
				}
				else if (mouse_x > 140 && mouse_x < 210) {
					MessageBox(hWnd, pos[26], L"Message", NULL);
				}
				else if (mouse_x > 210 && mouse_x < 280) {
					MessageBox(hWnd, pos[27], L"Message", NULL);
				}
				else if (mouse_x > 280 && mouse_x < 350) {
					MessageBox(hWnd, pos[28], L"Message", NULL);
				}
				else if (mouse_x > 350 && mouse_x < 420) {
					MessageBox(hWnd, pos[29], L"Message", NULL);
				}
				else if (mouse_x > 420 && mouse_x < 490) {
					MessageBox(hWnd, pos[30], L"Message", NULL);
				}
				else if (mouse_x > 490 && mouse_x < 590) {
					MessageBox(hWnd, pos[31], L"Message", NULL);
				}
			}
			else if (mouse_y > 280 && mouse_y < 350) {
				if (mouse_x < 70) {
					MessageBox(hWnd, pos[32], L"Message", NULL);
				}
				else if (mouse_x > 70 && mouse_x < 140) {
					MessageBox(hWnd, pos[33], L"Message", NULL);
				}
				else if (mouse_x > 140 && mouse_x < 210) {
					MessageBox(hWnd, pos[34], L"Message", NULL);
				}
				else if (mouse_x > 210 && mouse_x < 280) {
					MessageBox(hWnd, pos[35], L"Message", NULL);
				}
				else if (mouse_x > 280 && mouse_x < 350) {
					MessageBox(hWnd, pos[36], L"Message", NULL);
				}
				else if (mouse_x > 350 && mouse_x < 420) {
					MessageBox(hWnd, pos[37], L"Message", NULL);
				}
				else if (mouse_x > 420 && mouse_x < 490) {
					MessageBox(hWnd, pos[38], L"Message", NULL);
				}
				else if (mouse_x > 490 && mouse_x < 590) {
					MessageBox(hWnd, pos[39], L"Message", NULL);
				}
			}
			else if (mouse_y > 350 && mouse_y < 420) {
				if (mouse_x < 70) {
					MessageBox(hWnd, pos[40], L"Message", NULL);
				}
				else if (mouse_x > 70 && mouse_x < 140) {
					MessageBox(hWnd, pos[41], L"Message", NULL);
				}
				else if (mouse_x > 140 && mouse_x < 210) {
					MessageBox(hWnd, pos[42], L"Message", NULL);
				}
				else if (mouse_x > 210 && mouse_x < 280) {
					MessageBox(hWnd, pos[43], L"Message", NULL);
				}
				else if (mouse_x > 280 && mouse_x < 350) {
					MessageBox(hWnd, pos[44], L"Message", NULL);
				}
				else if (mouse_x > 350 && mouse_x < 420) {
					MessageBox(hWnd, pos[45], L"Message", NULL);
				}
				else if (mouse_x > 420 && mouse_x < 490) {
					MessageBox(hWnd, pos[46], L"Message", NULL);
				}
				else if (mouse_x > 490 && mouse_x < 590) {
					MessageBox(hWnd, pos[47], L"Message", NULL);
				}
			}
			else if (mouse_y > 420 && mouse_y < 490) {
				if (mouse_x < 70) {
					MessageBox(hWnd, pos[48], L"Message", NULL);
				}
				else if (mouse_x > 70 && mouse_x < 140) {
					MessageBox(hWnd, pos[49], L"Message", NULL);
				}
				else if (mouse_x > 140 && mouse_x < 210) {
					MessageBox(hWnd, pos[50], L"Message", NULL);
				}
				else if (mouse_x > 210 && mouse_x < 280) {
					MessageBox(hWnd, pos[51], L"Message", NULL);
				}
				else if (mouse_x > 280 && mouse_x < 350) {
					MessageBox(hWnd, pos[52], L"Message", NULL);
				}
				else if (mouse_x > 350 && mouse_x < 420) {
					MessageBox(hWnd, pos[53], L"Message", NULL);
				}
				else if (mouse_x > 420 && mouse_x < 490) {
					MessageBox(hWnd, pos[54], L"Message", NULL);
				}
				else if (mouse_x > 490 && mouse_x < 590) {
					MessageBox(hWnd, pos[55], L"Message", NULL);
				}
			}
			else if (mouse_y > 490 && mouse_y < 590) {
				if (mouse_x < 70) {
					MessageBox(hWnd, pos[56], L"Message", NULL);
				}
				else if (mouse_x > 70 && mouse_x < 140) {
					MessageBox(hWnd, pos[57], L"Message", NULL);
				}
				else if (mouse_x > 140 && mouse_x < 210) {
					MessageBox(hWnd, pos[58], L"Message", NULL);
				}
				else if (mouse_x > 210 && mouse_x < 280) {
					MessageBox(hWnd, pos[59], L"Message", NULL);
				}
				else if (mouse_x > 280 && mouse_x < 350) {
					MessageBox(hWnd, pos[60], L"Message", NULL);
				}
				else if (mouse_x > 350 && mouse_x < 420) {
					MessageBox(hWnd, pos[61], L"Message", NULL);
				}
				else if (mouse_x > 420 && mouse_x < 490) {
					MessageBox(hWnd, pos[62], L"Message", NULL);
				}
				else if (mouse_x > 490 && mouse_x < 590) {
					MessageBox(hWnd, pos[63], L"Message", NULL);
				}
			}
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 64; i++) {
			if (i % 8 == 0 && i != 0) {
				x_left = 0;
				x_right = CELL_SIZE;
				y_left += CELL_SIZE;
				y_right += CELL_SIZE;
				count = -count;
			}
			if (count > 0) {
				SelectObject(hdc, GetStockObject(GRAY_BRUSH));
				Rectangle(hdc, x_left, y_left, x_right, y_right);
			}
			else {
				SelectObject(hdc, GetStockObject(BLACK_BRUSH));
				Rectangle(hdc, x_left, y_left, x_right, y_right);
			}
			count = -count;
			x_left += CELL_SIZE;
			x_right += CELL_SIZE;
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		//DeleteObject(darkBrush);
		//DeleteObject(lightBrush);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
