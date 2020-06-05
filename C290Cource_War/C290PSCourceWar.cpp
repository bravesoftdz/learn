#include <iostream>
// ������� ����������
#include "lib/ApplicationConsts.h"
#include "lib/ApplicationGlobals.h"
#include "lib/Application.h"
#include "lib/Console.h"
#include "lib/Directory.h"
#include "lib/Environment.h"
#include "lib/Path.h"
#include "lib/StringHelper.h"
// ���������� ������ ������ ����������
#include "data/DataItem.h"
#include "data/DataGoods.h"
#include "data/DataWarrior.h"


void App_OnEscape(Application* Sender) {
	Sender->Running = false;
}

char* GAppDefaultDocPath     = NULL;
char* GAppDefaultFileWarrior = NULL;
char* GAppDefaultFileGoods   = NULL;

Warrior* GWarriors;
Good* GGoods;

int main() {
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
	// 1.5. ���������� ���� ���� � ���������� ���������� GAppDefaultDocPath
	GAppDefaultDocPath = StringHelper::New();
	strcpy_s(GAppDefaultDocPath, StringHelper::DefaultSize, LMyDocuments);
	Path::Combine(GAppDefaultDocPath, ApplicationFolder);
	// 1.6. ����� LMyDocuments ������ �� �����
	free(LMyDocuments);
	// 2. ������ ������, �������� ����� ������ � �������
	// 2.1 ��� ������
	GAppDefaultFileWarrior = StringHelper::New();
	strcpy_s(GAppDefaultFileWarrior, StringHelper::DefaultSize, GAppDefaultDocPath);
	Path::Combine(GAppDefaultFileWarrior, DefaultFileNameWarriors);
	// 2.2 ��� ����� �����������
	GAppDefaultFileGoods = StringHelper::New();
	strcpy_s(GAppDefaultFileGoods, StringHelper::DefaultSize, GAppDefaultDocPath);
	Path::Combine(GAppDefaultFileGoods, DefaultFileNameGoods);
	// 3. �������� ���������� �������� - ������� ������
	GWarriors = (Warrior*)Warrior::ListLoadFromFile(GAppDefaultFileWarrior);
	GGoods    = (Good   *)Good::ListLoadFromFile(GAppDefaultFileGoods);
	// 3.1 ������ ��� ��������:
	//     ���� ��� ����������� �������, ���������� �������� ������
	if (NULL == GWarriors) {
		for (int i = 0; i < 20; i++) {
			Warrior *LItem = new Warrior();
			LItem->Id = (i + 1);
			LItem->GenTest();
			if (NULL == GWarriors) {
				GWarriors = LItem;
			} else {
				GWarriors = (Warrior*)GWarriors->ListAdd(LItem);
			}
		}
	}
	if (NULL == GGoods) {
		for (int i = 0; i < 200; i++) {
			Good* LItem = new Good();
			LItem->Id = (i + 1);
			LItem->GenTest();
			if (NULL == GGoods) {
				GGoods = LItem;
			} else {
				GGoods = (Good*)GGoods->ListAdd(LItem);
			}
		}
	}
	// 4. �������� ������ ����������
	Application* App = new Application();
	App->OnEscape = &App_OnEscape;
	//1. ���������� ����������
	//printf("%s\n", GAppDefaultDocPath);
	//printf("%s\n", GAppDefaultFileWarrior);
	//printf("%s\n", GAppDefaultFileGoods);
	App->Run();
	delete App;



	// 98. ��������� ������ � �����
	GWarriors->ListSaveToFile(GAppDefaultFileWarrior);
	GGoods->ListSaveToFile(GAppDefaultFileGoods);
	// 99. ������������ ������
	free(GAppDefaultFileGoods);
	free(GAppDefaultFileWarrior);
	free(GAppDefaultDocPath);
	return 0;
}