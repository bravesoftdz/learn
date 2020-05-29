#include <iostream>
#include <Windows.h>

const int StrDefaultSize = 255;

void StrNull(char* str, const int length = StrDefaultSize) {
	for (int i = 0; i < length; i++) {
		*(str + i) = 0;
	}
};

void StrInput(char* str, const int length = StrDefaultSize) {
	char* s = str;
	int i = 0;
	*s = getchar();
	while ((i < (length - 2)) && (*s != '\n')) {
		s++;
		i++;
		*s = getchar();
	}
	*s = 0;
};

char* StrNew(const int length = StrDefaultSize) {
	char* LStr = (char*)malloc(length * sizeof(char));
	StrNull(LStr, length);
	return LStr;
};

void StrToUpper(char* str, const int length = StrDefaultSize) {
	for (int i = 0; i < length; i++) {
		*(str + i) = toupper(*(str + i));
	}
};

const int CTownsCount = 21;

const char* CTowns[CTownsCount] = {
	 "����\0"
	,"���������\0"
	,"�����\0"
	,"������\0"
	,"�������\0"
	,"�������\0"
	,"������ ���\0"
	,"����������\0"
	,"���\0"
	,"������\0"
	,"������\0"
	,"������\0"
	,"����\0"
	,"��������\0"
	,"����������\0"
	,"���������\0"
	,"����\0"
	,"��������\0"
	,"�������\0"
	,"�����\0"
	,"�������\0"
};

struct Train {
	int Id;          // ����� ������ 91 �� ������1 � �����2, �� ���� � 92 �� ������2 � �����1
	char* TownFrom;  // �� ������
	char* TownTo;    // � �����
};


int main() {
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	///
	int i;
	const int LCTraintCount = 6;
	struct Train* Trains = (Train*)malloc(LCTraintCount * sizeof(struct Train));
	// 1.���� ������
	char* LBufferId    = StrNew();
	char* LBufferTown1 = StrNew();
	char* LBufferTown2 = StrNew();
	for (i = 0; i < LCTraintCount; i = i + 2) {
        // �������� ������� ������
		StrNull(LBufferId);
		StrNull(LBufferTown1);
		StrNull(LBufferTown2);
		// ����� "����"
		printf("���� ������ %d :\n", i);
		printf("   -- ������� ����� ������:");
		StrInput(LBufferId);
		printf("   -- ������� ����� ������:");
		StrInput(LBufferTown1);
		printf("   -- ������� ����� ����:");
		StrInput(LBufferTown2);

		(Trains + i)->Id = atoi(LBufferId);  // ���������� �������� ������ �����
		(Trains + i)->TownFrom = StrNew();
		strcpy_s((Trains + i)->TownFrom, StrDefaultSize, LBufferTown1);
		(Trains + i)->TownTo   = StrNew();
		strcpy_s((Trains + i)->TownTo, StrDefaultSize, LBufferTown2);

		// ����� "�������"
		(Trains + i + 1)->Id = atoi(LBufferId) + 1; // ����� ������ "�������" ����� ������ ������ "����" + 1
		(Trains + i + 1)->TownFrom = StrNew();
		strcpy_s((Trains + i + 1)->TownFrom, StrDefaultSize, LBufferTown2);
		(Trains + i + 1)->TownTo = StrNew();
		strcpy_s((Trains + i + 1)->TownTo, StrDefaultSize, LBufferTown1);
	}
	free(LBufferTown2);
	free(LBufferTown1);
	free(LBufferId);

	// 2. ����������� ����� ������� - ���������� �������
	printf("=====================================================\n");
	printf("|                 ���������� �������                |\n");
	printf("-----------------------------------------------------\n");
	printf("|  �  |        ������        |         ����         |\n");
	printf("=====================================================\n");
	for (i = 0; i < LCTraintCount; i++) {
		printf("| %3d | %-20s | %-20s |\n", (Trains+i)->Id, (Trains+i)->TownFrom, (Trains+i)->TownTo);
	}
	printf("=====================================================\n");
	// 3. ����� �������, ���������� ����� ����������� �������
	char* TownName = StrNew();
	printf("\n");
	printf("������� ��������� � ���� ����� ������:");
	StrInput(TownName);
	printf("=====================================================\n");
	printf("| ������ ������ ����� ����� %s         |\n", TownName);
	printf("-----------------------------------------------------\n");
	printf("|  �  |        ������        |         ����         |\n");
	printf("=====================================================\n");

	StrToUpper(TownName);
	char* BufferTownFrom = StrNew();
	char* BufferTownTo = StrNew();

	int TrainsCount = 0;
	for (i = 0; i < LCTraintCount; i++) {
		StrNull(BufferTownFrom); 
		strcpy_s(BufferTownFrom, StrDefaultSize, (Trains + i)->TownFrom);
		StrToUpper(BufferTownFrom);
		
		StrNull(BufferTownTo  ); 
		strcpy_s(BufferTownTo  , StrDefaultSize, (Trains + i)->TownTo);
		StrToUpper(BufferTownTo);

		if (strstr(BufferTownFrom, TownName) != NULL) {
			printf("| %3d | %-20s | %-20s |\n", (Trains + i)->Id, (Trains + i)->TownFrom, (Trains + i)->TownTo);
			TrainsCount++;
		}
		if (strstr(BufferTownTo, TownName) != NULL) {
			printf("| %3d | %-20s | %-20s |\n", (Trains + i)->Id, (Trains + i)->TownFrom, (Trains + i)->TownTo);
			TrainsCount++;
		}
	}
	if (0 == TrainsCount) {
		printf("|           ������� � ���� ������ ���               |\n");
	}
	printf("=====================================================\n");

	// ������������ ������
	free(BufferTownFrom);
	free(BufferTownTo);
	free(TownName);
	for (i = 0; i < LCTraintCount; i++) {
		free((Trains + i)->TownFrom);
		free((Trains + i)->TownTo);
	}
	free(Trains);
	return 0;

}