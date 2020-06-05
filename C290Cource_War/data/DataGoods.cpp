#include <iostream>
#include "../lib/StringHelper.h"
#include "DataItem.h"
#include "DataGoods.h"

Good::Good() {
	Position = StringHelper::New();
	Foot     = -1;
	Height   = -1;
	Massa    = 0.;
	Quant    = 0.;
}

Good::~Good() {
	free(Position);
}

void Good::GenTest() {
	const int LCNamesCount = 5;
	const char* LCNames[LCNamesCount] = {
		  "�����\0"
		, "������\0"
		, "�����\0"
		, "�����\0"
		, "������\0"
	};
	const int LCPositionsCount = 5;
	const char* LCPositions[LCPositionsCount] = {
		  "���������\0"
		, "����������\0"
		, "��������\0"
		, "���������\0"
		, "�����\0"
	};

	int r;
	r = rand() % LCNamesCount;
	strcpy_s(Name, StringHelper::DefaultSize, LCNames[r]);
	if (0 == r) {
		Height = 1 + (rand() % 4);
	}
	if( (1 == r) || (2 == r)  ){
		Foot = 38 + (rand() % 8);
	}
	r = rand() % LCPositionsCount;
	strcpy_s(Position, StringHelper::DefaultSize, LCPositions[r]);
	
	Massa = 0.001 + (rand() % 1000) / 1000.;
	Quant = 1 + rand() % 5;
}

void Good::ListSaveToFileItem(FILE* FileHandle) {
	fprintf(FileHandle, "%d|%s|%s|%d|%d|%f|%f\n", Id, Name, Position, Foot, Height, Massa, Quant);
}

char* Good::LoadFromString(char* Text) {
	char* LParser = Item::LoadFromString(Text);

	char* LTempPosition = StringHelper::New();
	char* LTempFoot     = StringHelper::New();
	char* LTempHeight   = StringHelper::New();
	char* LTempMassa    = StringHelper::New();
	char* LTempQuant    = StringHelper::New();

	LParser = StringHelper::Parse(LParser, '|', LTempPosition);
	LParser = StringHelper::Parse(LParser, '|', LTempFoot);
	LParser = StringHelper::Parse(LParser, '|', LTempHeight);
	LParser = StringHelper::Parse(LParser, '|', LTempMassa);
	LParser = StringHelper::Parse(LParser, '|', LTempQuant);

	strcpy_s(Position, StringHelper::DefaultSize, LTempPosition);
	Foot   = atoi(LTempFoot);
	Height = atoi(LTempHeight);
	Massa  = atof(LTempMassa);
	Quant  = atof(LTempQuant);

	free(LTempQuant);
	free(LTempMassa);
	free(LTempHeight);
	free(LTempFoot);
	free(LTempPosition);

	return LParser;
}