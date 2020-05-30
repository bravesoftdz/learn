#include <iostream>
#include <Windows.h>
#include <ShlObj.h>
#include <Shlwapi.h>
#include <locale.h>
#include "ApplicationConsts.h"
#include "StringHelper.h"
#include "TGeoObject.h"
#include "TGeoObjectHouse.h"
#include "TGeoObjectShop.h"
#include "TGeoObjectBank.h"
#include "Environment.h"
#include "Directory.h"
#include "Path.h"



int main() {
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char* Folder = StringHelper::New();
	// 1. ��������� �������� ���� ��� ����������
	Environment::GetCurrentDir(Folder);
	printf("Current Directory = %s\n", Folder);
    // 2. ���������� ������� �������� ��� ����������
	Environment::SetCurrentDir("d:\\");
	// 2.1 ��������
	Environment::GetCurrentDir(Folder);
	printf("Current Directory = %s\n", Folder);
	// 3. ��������� ����������� ����� Windows
	// 3.1. �������� ���� � �������� "��� ���������"
	char* MyDoc = Environment::GetFolderPath(Environment::MyDocuments);
	printf("MyDocuments path = %s\n", MyDoc);
	// 4. ������������� ������� ���� � ����� "��� ���������"
	Environment::SetCurrentDir(MyDoc);
		
	if (!Directory::Exists(ApplicationFolder)) {
		Directory::Create(ApplicationFolder);
	}
	// 5. ������������� ������� ���� "��� ���������" \ "������� ������ ����������" 
	Path::Combine(MyDoc, ApplicationFolder);
	Environment::SetCurrentDir(MyDoc);
	// 2.1 ��������
	Environment::GetCurrentDir(Folder);
	printf("Current Directory = %s\n", Folder);


	free(MyDoc);
	free(Folder);
	Console::GotoXY(0, 40);
	Console::SetColor(Console::DefaultColor, Console::DefaultBgColor);

	return 0;
}