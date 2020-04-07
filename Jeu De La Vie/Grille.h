#pragma once
#include "Cellule.h"
#include <vector>
#include <Windows.h>

class Grille
{
public:

private:
	int x;
	int y;
	std::vector<std::vector<Cellule>> myArray;
public:
	Grille(int x, int y) {
		this->x = x;
		this->y = y;
		for (int i = 0; i < x; i++) {
			std::vector<Cellule> temp;
			for (int j = 0; j < x; j++) {
				temp.push_back(Cellule{ false,i,j });
			}
			myArray.push_back(temp);
		}
	}

	void paintAll(HWND hWnd) {
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < x; j++) {
				myArray[i][j].paint(hWnd);
			}
		}
	}

	void paint(HWND hWnd, int x, int y) {
		myArray[x][y].paint(hWnd);
	}

	void kill(int x, int y) {
		myArray[x][y].kill();
	}

	void resurrect(int x, int y) {
		myArray[x][y].resurrect();
	}

	void killAll() {
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < x; j++) {
				myArray[i][j].kill();
			}
		}
	}

	void resurrectAll() {
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < x; j++) {
				myArray[i][j].resurrect();
			}
		}
	}

	bool isAlive(int x, int y) {
		return myArray[x][y].isAlive();
	}



};

