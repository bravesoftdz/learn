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
public:	// ������ ������ ��� ������ � �������, ��� � ���������� �������
	virtual void ListSaveToFileItem(FILE* FileHandle);
	virtual char* LoadFromString(char* Text);
	static Warrior* ListLoadFromFile(const char* FileName);
};

#endif