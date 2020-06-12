#include <iostream>
#include <Windows.h>
#include "lib/ApplicationConsts.h"
#include "lib/Environment.h"
#include "lib/Directory.h"
#include "lib/Path.h"
#include "lib/Console.h"
#include "lib/StringHelper.h"

int main() {
    setlocale(LC_ALL, ".1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	// 1. ���������� ����� � �������� ������� ��� ������ ����������
	// 1.1. �������� ���� � ����� "��� ���������"
	char* LMyDocuments = Environment::GetFolderPath(Environment::MyDocuments);
	// 1.2 ������������� ���� � ����� "��� ���������" - ������� ��� ���������
	Environment::SetCurrentDir(LMyDocuments);
	// 1.3. ���������, ���������� �� ������� "��� ���������" \ ApplicationFolder
	if (!Directory::Exists(ApplicationFolder)) { // ���� ������� �� ����������
		Directory::Create(ApplicationFolder); // ������ ���
	}
	// 1.4. ������������� ������� �������  "��� ���������" \ ApplicationFolder
	Environment::SetCurrentDir(ApplicationFolder);
	// 1.5. ���������� ���� ���� � ���������� ����������  LDefaultFileSettingsPath

	char* LDefaultFileSettingsPath = StringHelper::New();
	strcpy_s(LDefaultFileSettingsPath, StringHelper::DefaultSize, LMyDocuments);
	Path::Combine(LDefaultFileSettingsPath, ApplicationFolder);
	Path::Combine(LDefaultFileSettingsPath, DefaultFileNameSettings);
	// 1.6. ����� LMyDocuments ������ �� �����
	free(LMyDocuments);
	// �������: ������� � ������� ���� � ����� ��������
	//printf("%s\n", LDefaultFileSettingsPath);
	Console::ConsoleColors ColorBgr = Console::clBlack;
	Console::ConsoleColors ColorFrg = Console::clCyan;
	// �������� �������� �� �����
	if (Directory::Exists(LDefaultFileSettingsPath)) {
		FILE *FileSettings;
		int FileSettingsOpenError = fopen_s(&FileSettings, LDefaultFileSettingsPath, "r");
		if (0 == FileSettingsOpenError) {
			fscanf_s(FileSettings, "%d\n", &ColorBgr);
			fscanf_s(FileSettings, "%d\n", &ColorFrg);
			fclose(FileSettings);
		}
	}
	Console::SetColor(ColorFrg, ColorBgr);
	// ��� ������ ���� ���������
	for (int i = 0; i < 40; i++) {
		printf("| %8d | %8d | %8d | %8d |\n", i, i*2, i*3, i*4);
	}
    // ��������� ��������� � ����
	FILE* LFileSettings;
	int LFileSettingsOpenError = fopen_s(&LFileSettings, LDefaultFileSettingsPath, "w+");
	if (0 == LFileSettingsOpenError) {
		fprintf(LFileSettings, "%d\n", (int)ColorBgr);
		fprintf(LFileSettings, "%d\n", (int)ColorFrg);
		fclose(LFileSettings);
	}


	free(LDefaultFileSettingsPath);
    return 0;
}