#ifndef DATAGOODS_H
#define DATAGOODS_H

#include "DataItem.h"

class Good :public Item {
public:
	// ���� ������ �����������
	char* Position;
	int Foot;
	int Height;
	double Massa;
	double Quant;
	// �����������
	Good();
	~Good();
	// ������ ������
	virtual void GenTest();
	virtual void PrintInternal();
	static void PrintHeader(const short X, const short Y, const Console::ConsoleColors Foreground, const Console::ConsoleColors Background = Console::clBlack);
public:	// ������ ������ ��� ������ � �������, ��� � ���������� �������
	virtual void ListSaveToFileItem(FILE* FileHandle);
	virtual char* LoadFromString(char* Text);
	static Good* ListLoadFromFile(const char* FileName);
};

#endif