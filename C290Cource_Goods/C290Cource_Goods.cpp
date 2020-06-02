#include <iostream>
#include <Windows.h>
// ��������� ����������
#include "lib/Console.h"
#include "lib/Directory.h"
#include "lib/Environment.h"
#include "lib/Path.h"
#include "lib/StringHelper.h"
#include "lib/Application.h"
// ������ ������ ������
#include "data/DataModelTMC.h"
// ��������� ���������
#include "lib/ApplicationConsts.h"
#include "lib/ApplicationGlobals.h"


// ������������� ���������� ����������
char* ApplicationPathFolder  = NULL;
char* ApplicationPathFileTMC = NULL;

int main() {
	// 1. ��������� ����������� ��� ����������
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	// 2. ��������� ����������� ����� Windows
	// 2.1. �������� ���� � �������� "��� ���������"
	ApplicationPathFolder  = Environment::GetFolderPath(Environment::MyDocuments);
	ApplicationPathFileTMC = StringHelper::New();
	// 2.3. ������������� ������� ���� � ����� "��� ���������"
	Environment::SetCurrentDir(ApplicationPathFolder);
    // 2.4. ��������� ������������� �������� 
	if (!Directory::Exists(ApplicationFolder)) {
		Directory::Create(ApplicationFolder);
	}
	// 2.5. ������������� ������� ���� "��� ���������" \ "������� ������ ����������" 
	Path::Combine(ApplicationPathFolder, ApplicationFolder);
	Environment::SetCurrentDir(ApplicationPathFolder);
	// 2.6. ��������� ���� � ����� � �������
	strcpy_s(ApplicationPathFileTMC, StringHelper::DefaultSize, ApplicationPathFolder);
	Path::Combine(ApplicationPathFileTMC, ApplicationFileTMC);


	TMC* Goods = NULL;
	for (int i = 0; i < 200; i++) {
		TMC* LItem = new TMC();
		LItem->Id = i + 1;
		LItem->GenTest();
		if (NULL == Goods) {
			Goods = LItem; // ��� ������ ������� ��������
		} else {
			Goods = Goods->ListAdd(LItem);
		}
	}

	Goods->ListPrint();
	Goods->ListSave(ApplicationPathFileTMC);



	free(ApplicationPathFileTMC);
	free(ApplicationPathFolder);
	return 0;
}