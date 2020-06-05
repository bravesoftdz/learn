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
public:	// ������ ������ ��� ������ � �������, ��� � ���������� �������
	virtual void ListSaveToFileItem(FILE* FileHandle);
	virtual char* LoadFromString(char* Text);
};

#endif