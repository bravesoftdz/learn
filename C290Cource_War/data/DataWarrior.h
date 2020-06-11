#ifndef DATAWARRIOR_H
#define DATAWARRIOR_H

#include "DataItem.h"

class Warrior :public Item {
public:
	// ���� ������ ����
	char* Position;
	int Foot;
	int Height;
	// �����������
	Warrior();
	~Warrior();
	// ������ ������
	virtual void GenTest();
	virtual void PrintInternal();
	static void PrintHeader(const short X, const short Y, const Console::ConsoleColors Foreground, const Console::ConsoleColors Background = Console::clBlack);
public:	// ������ ������ ��� ������ � �������, ��� � ���������� �������
	virtual void ListSaveToFileItem(FILE* FileHandle);
	virtual char* LoadFromString(char* Text);
	static Warrior* ListLoadFromFile(const char* FileName);
};

#endif