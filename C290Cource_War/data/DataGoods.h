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
public:	// ������ ������ ��� ������ � �������, ��� � ���������� �������
	virtual void ListSaveToFileItem(FILE* FileHandle);
	virtual char* LoadFromString(char* Text);
};

#endif