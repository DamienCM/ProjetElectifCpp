#pragma once
#include <Windows.h>
class Cellule
{
public:

private:
	int x;
	int y;
	bool alive;

public:
	Cellule(bool alive, int x, int y) {
		this->x = x;
		this->y = y;
		this->alive = true;
	}
	void kill() {
		this->alive = false;
	}
	void resurrect() {
		this->alive = true;
	}
	bool isAlive() {
		return alive;
	}
	void paint(HWND hWnd) {
		HBRUSH brush;
		HPEN pen;
		if (alive) {
			brush = CreateSolidBrush(RGB(255, 255, 255));
			pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		}
		else {
			brush = CreateSolidBrush(RGB(0, 0, 0));
			pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		}
		HDC hdc = GetDC(hWnd);
		SelectObject(hdc, brush);
		SelectObject(hdc, pen);
		Rectangle(hdc, x * 10, y * 10, x * 10 + 10, y * 10 + 10);
		ReleaseDC(hWnd, hdc);
		DeleteObject(brush);
		DeleteObject(pen);
	}
};

