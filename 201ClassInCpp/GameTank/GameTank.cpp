#include "pch.h"
#include <iostream>
#include <conio.h>
#include "../ClassInCpp/consts.h"
#include "../ClassInCpp/strutils.h"
#include "../ClassInCpp/consoleroutine.h"
#include "../ClassInCpp/tgeom.h"
#include "../ClassInCpp/tpoint.h"
#include "../ClassInCpp/trect.h"
#include "../ClassInCpp/list2link.h"

void printStatus1(short x, short y, short Left, short Top) {
	char *s = (char *)malloc(255 * sizeof(char));
	nullStr(s, 255);
	strcpy_s(s, 255, "F3=Load");
	consoleSetColors(clBlack, clLightRed);
	consoleGotoXY(Left, Top);
	printf("x:3%d y:%3d      %s", x, y, s);
	free(s);
}

int main(){
	TRect *console = new TRect();
	console->setBounds(1, 1, consoleSizeY() - 2, consoleSizeX() - 2);

	TPoint *tank = new TPoint();
	tank->setX(console->getX() + console->getWidth() / 2);
	tank->setY(console->getY() + console->getHeight() / 2);
	tank->setTyp(ptTank);
	tank->setColor(clBlack);
	tank->setBgColor(clLightGreen);

	list2 *map = list2_loadfromfile(NULL, "d:\\map.txt");
	list2_print(map);

	int flagExit = 0;
	int keyPressed = 0;
	do {
		printStatus1(tank->getX(), tank->getY(), 0, 0);
		tank->Print();
		consoleGotoXY(tank->getX(), tank->getY());
		keyPressed = _getch();
		tank->Erase();
		switch (keyPressed) {
		    case KEY_ESCAPE: {
				flagExit = 1;
				break;
			}
		case KEY_LEFT: {
			if( (tank->getX() > console->getX()) && (0 == list2_contains(map, (tank->getX()-1), tank->getY())) ) {
				tank->setX(tank->getX() - 1);
			}
			break;
		}
		case KEY_RIGHT: {
			if( (tank->getX() < console->getWidth()) && (0 == list2_contains(map, (tank->getX() + 1), tank->getY())) ){
				tank->setX(tank->getX() + 1);
			}
			break;
		}
		case KEY_UP: {
			if( (tank->getY() > console->getY()) && (0 == list2_contains(map, tank->getX(), (tank->getY()-1))) ){
				tank->setY(tank->getY() - 1);
			}
			break;
		}
		case KEY_DOWN: {
			if( (tank->getY() < console->getHeight()) && (0 == list2_contains(map, tank->getX(), (tank->getY()+1))) ){
				tank->setY(tank->getY() + 1);
			}
			break;
		}
		}
	} while (0 == flagExit);

	delete tank;
	//delete console;

	consoleSetColors(clWhite, clBlack);
	return 0;// gg Dortmund
}