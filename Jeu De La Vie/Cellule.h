#pragma once
#include <Windows.h>
#include "Log.h"
static HBRUSH brushNoir= CreateSolidBrush(RGB(0,0,0));
static HBRUSH brushBlanc=CreateSolidBrush(RGB(255, 255, 255));
static HPEN penNoir= CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
static HPEN penBlanc= CreatePen(PS_SOLID, 1, RGB(255,255,255));
static Log logCellule{ "logCellule.txt" };

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
		this->alive = alive;

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

		HDC hdc = GetDC(hWnd);

		if (alive) {
			SelectObject (hdc, penBlanc);
			SelectObject(hdc, brushBlanc);
			logCellule.Info("BLANC");
		}
		else {
			SelectObject(hdc, brushNoir);
			SelectObject(hdc, penNoir);
			logCellule.Warning("NOIR");
		}
		Rectangle(hdc, x * 10, y * 10, x * 10 + 10, y * 10 + 10);
		ReleaseDC(hWnd, hdc);
	}
};

