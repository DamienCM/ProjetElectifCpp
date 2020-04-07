#include "framework.h"
#include "Jeu De La Vie.h"
#include "Log.h"
#include "Cellule.h"
#include <iostream>
#include <string>

int main() {
	Log logTest{ "logTest.txt" };

	Cellule myCellA{ true,1,1 };
	Cellule myCellB{ false,1,1 };

	myCellB.copyState(myCellA);
	std::string str = std::to_string(myCellB.isAlive());
	logTest.Error(str.c_str());
	logTest.Info("abajdbakzjb");
	return 0;
}


