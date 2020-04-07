#pragma once
#include "Cellule.h"
#include <vector>
#include <Windows.h>
#include "Log.h"
#include <string>

static Log logGrille{ "logGrille.txt" };


class Grille
{
public:

private:
	int x;
	int y;
	std::vector<std::vector<Cellule>> currentArray;
	std::vector<std::vector<Cellule>> nextArray;

public:
	Grille(int x, int y) {
		this->x = x;
		this->y = y;
		for (int i = 0; i < x; i++) {
			std::vector<Cellule> temp1;
			std::vector<Cellule> temp2;
			for (int j = 0; j < x; j++) {
				temp1.push_back(Cellule{ false,i,j });
				temp2.push_back(Cellule{ false,i,j });
			}
			currentArray.push_back(temp1);
			nextArray.push_back(temp2);
		}
	}

	void paintAll(HWND hWnd) {
		logGrille.Error("paintAll");
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < x; j++) {
				currentArray[i][j].paint(hWnd);
			}
		}
	}

	void paint(HWND hWnd, int x, int y) {
		currentArray[x][y].paint(hWnd);
	}

	void kill(int x, int y) {
		currentArray[x][y].kill();
	}

	void resurrect(int x, int y) {
		currentArray[x][y].resurrect();
	}

	void killAll() {
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < x; j++) {
				currentArray[i][j].kill();
			}
		}
	}

	void resurrectAll() {
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++) {
				currentArray[i][j].resurrect();
			}
		}
	}

	bool isAlive(int x, int y) {
		return currentArray[x][y].isAlive();
	}

	void update(HWND hWnd) {
		int delta = 1;

		for (int i = 0 +delta; i < x-delta; i++) {
			for (int j = 0+delta; j < y-delta; j++) {
				Cellule cell = currentArray[i][j];
				Cellule nextCell = nextArray[i][j];

				Cellule celluleTab[8] = {
					currentArray[i - 1][j - 1], currentArray[i][j - 1], currentArray[i + 1][j - 1],
					currentArray[i - 1][j],					      currentArray[i + 1][j],
					currentArray[i - 1][j + 1], currentArray[i][j + 1], currentArray[i + 1][j + 1]
				};
				int count = 0;
				if (cell.isAlive()) {
					for (int k = 0; k < 8; k++) {
						if (celluleTab[k].isAlive()) {
							count = count + 1;
						}
					}

					if (count == 2 || count == 3) {
						nextCell.resurrect();
					}
					else {
						nextCell.kill();

					}
				}
				else {
					for (int k = 0; k < 8; k++) {
						if (celluleTab[k].isAlive()) {
							count = count + 1;
						}
					}
					if (count == 3) {
						nextCell.resurrect();

					}
					else {
						nextCell.kill();
					}

				}

				nextArray[i][j] = nextCell;

			}
		}
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++) {
				if (currentArray[i][j].copyState(nextArray[i][j])) {
					currentArray[i][j].paint(hWnd);
				}
			}
			
		}
	}

};

