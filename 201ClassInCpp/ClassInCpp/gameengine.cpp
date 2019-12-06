#include "pch.h"
#include <iostream>
#include <conio.h>
#include "consts.h"
#include "strutils.h"
#include "tgeom.h"
#include "tpoint.h"
#include "trect.h"
#include "tcircle.h"
#include "list2link.h"
#include "consoleroutine.h"
#include "gameengine.h"

GameEngine::GameEngine() {
	Running = 0;
	
	Console = new TRect();
	Console->setBounds(1, 1, consoleSizeY() - 2, consoleSizeX() - 2);
	
	Tank = new TPoint();
	Tank->setX(Console->getX() + Console->getWidth()  / 2);
	Tank->setY(Console->getY() + Console->getHeight() / 2);
	Tank->setTyp(ptTank);
	Tank->setColor(clBlack);
	Tank->setBgColor(clLightRed);

	Map = list2_loadfromfile(NULL, "d:\\map3.txt");
};

GameEngine::~GameEngine() {
//	list2_clear(Map);
//	delete Tank;
//	delete Console;
	consoleSetColors(clWhite, clBlack);
};

void GameEngine::Run() {
	doRunBefore();
	Running = 1;
	while (0 != Running) {
		doProcessKeyBefore();
		doProcessKey( _getch() );
		doProcessKeyAfter();
	}
	doRunAfter();
};

void GameEngine::doRunBefore() {
	list2_print(Map);
};

void GameEngine::doRunAfter() {
};

void GameEngine::doProcessKeyBefore() {
	Tank->Print();
	consoleGotoXY(Tank->getX(), Tank->getY() );
};

void GameEngine::doProcessKeyAfter() {

};


void GameEngine::doProcessKey(int pressedKey) {
	switch (pressedKey) {
	    case KEY_ESCAPE: {doKeyEscape(); break; }
	    case KEY_LEFT  : {doKeyLeft()  ; break; }
	    case KEY_RIGHT : {doKeyRight() ; break; }
	    case KEY_UP    : {doKeyUp()    ; break; }
	    case KEY_DOWN  : {doKeyDown()  ; break; }
		case KEY_F1    : {doKeyF1()    ; break; }
		case KEY_F2    : {doKeyF2()    ; break; }
		case KEY_F3    : {doKeyF3()    ; break; }
		case KEY_F4    : {doKeyF4()    ; break; }
		case KEY_F5    : {doKeyF5()    ; break; }
		case KEY_F6    : {doKeyF6()    ; break; }
		case KEY_F7    : {doKeyF7()    ; break; }
		case KEY_F8    : {doKeyF8()    ; break; }
		case KEY_F9    : {doKeyF9()    ; break; }
		case KEY_F10   : {doKeyF10()   ; break; }
		case KEY_F11   : {doKeyF11()   ; break; }
		case KEY_F12   : {doKeyF12()   ; break; }
	}
};

void GameEngine::doKeyEscape() {
	Running = 0;
};

void GameEngine::doKeyLeft() {
	if ( (Tank->getX() > Console->getX()) && (1 != list2_contains(Map, Tank->getX() - 1, Tank->getY()) ) ) {
		Tank->setX(Tank->getX() - 1);
	}
};

void GameEngine::doKeyRight() {
	if( (Tank->getX() < Console->getWidth()) && (1 != list2_contains(Map, Tank->getX() + 1, Tank->getY()))) {
		Tank->setX(Tank->getX() + 1);
	}
};

void GameEngine::doKeyUp() {
	if( (Tank->getY() > Console->getY()) && (1 != list2_contains(Map, Tank->getX(), Tank->getY()-1))) {
		Tank->setY(Tank->getY() - 1);
	}
};

void GameEngine::doKeyDown() {
	if( (Tank->getY() < Console->getHeight()) && (1 != list2_contains(Map, Tank->getX(), Tank->getY() + 1))) {
		Tank->setY(Tank->getY() + 1);
	}
};

void GameEngine::doKeyF1() {

};

void GameEngine::doKeyF2() {

};

void GameEngine::doKeyF3() {

};

void GameEngine::doKeyF4() {

};

void GameEngine::doKeyF5() {

};

void GameEngine::doKeyF6() {

};

void GameEngine::doKeyF7() {

};

void GameEngine::doKeyF8() {

};

void GameEngine::doKeyF9() {

};

void GameEngine::doKeyF10() {

};

void GameEngine::doKeyF11() {

};

void GameEngine::doKeyF12() {

};

int GameEngine::getRunning() {
	return Running;
};

void GameEngine::setRunning(const int value) {
	if (value != Running) {
		Running = value;
	}
};