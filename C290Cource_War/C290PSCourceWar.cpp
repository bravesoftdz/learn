#include <iostream>
#include <conio.h>
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


void AppGoods_OnCommand(ApplicationConsole* Sender, int Command) {
	switch (Command) {
	   case 0: {
		   Console::GotoXY(0, 0);
		   Console::SetColor(Console::clLightGreen);
		   Console::FillRect(' ', 0 ,0, Console::Height(), Console::Width());
		   if (NULL != GGoods) {
			   Good *LGood = (Good*)GGoods->ListFirst();
			   while(NULL != LGood) {
				   printf("%3d|%-20s |\n", LGood->Id, LGood->Name);
				   LGood = (Good*)LGood->ListNext;
			   }
		   }
		   int i = _getch();
		   break;
	   }
	   case 1: {
		   break;
	   }
	   case 2: {
		   Sender->Running = false;
		   break;
	   }
	}
}

void AppWarriors_OnCommand(ApplicationConsole* Sender, int Command) {
	switch (Command) {
	case 0: {
		break;
	}
	case 1: {
		break;
	}
	case 2: {
		Sender->Running = false;
		break;
	}
	}
}

void App_OnEscape(Application* Sender) {
	Sender->Running = false;
}

void App_OnCommand(ApplicationConsole* Sender, int Command) {
	switch (Command) {
	    case 0: {
			ApplicationConsole* LAppGoods = new ApplicationConsole();
			LAppGoods->MenuMain->AddItem("1. ���������� ������ ����������� ");
			LAppGoods->MenuMain->AddItem("2. �������� ������� ����������� ");
			LAppGoods->MenuMain->AddItem("3. [Esc] ����� � ������� ���� ");
			LAppGoods->MenuMain->Selected = 0;
			LAppGoods->OnCommand = &AppGoods_OnCommand;
			LAppGoods->OnEscape = &App_OnEscape;
			LAppGoods->Run();
			delete LAppGoods;
			break; 
		}
		case 1: {
			ApplicationConsole* LAppWarriors = new ApplicationConsole();
			LAppWarriors->MenuMain->AddItem("1. ���������� ������ ����������� ");
			LAppWarriors->MenuMain->AddItem("2. �������� ������ ���������� ");
			LAppWarriors->MenuMain->AddItem("3. [Esc] ����� � ������� ���� ");
			LAppWarriors->MenuMain->Selected = 0;
			LAppWarriors->OnCommand = &AppWarriors_OnCommand;
			LAppWarriors->OnEscape = &App_OnEscape;
			LAppWarriors->Run();
			delete LAppWarriors;
			break;
	    }
		case 2: { 
			Sender->Running = false;
			break; 
		}
	}
}

char* GAppDefaultDocPath     = NULL;
char* GAppDefaultFileWarrior = NULL;
char* GAppDefaultFileGoods   = NULL;

Warrior* GWarriors = NULL;
Good* GGoods = NULL;

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
	Console::SetScreen(120, 80);
	// 4. �������� ������ ����������
	ApplicationConsole* App = new ApplicationConsole();
	App->MenuMain->AddItem("1. ����������� ");
	App->MenuMain->AddItem("2. ���������� ");
	App->MenuMain->AddItem("3. [Esc] ����� �� ��������� ");
	App->MenuMain->Selected = 0;
	App->OnCommand = &App_OnCommand;
	App->OnEscape  = &App_OnEscape;
	//1. ���������� ����������
	//printf("%s\n", GAppDefaultDocPath);
	//printf("%s\n", GAppDefaultFileWarrior);
	//printf("%s\n", GAppDefaultFileGoods);
	App->Run();
	delete App;
	// ������� ������� ����� ������� �� ���������
	Console::SetColor(Console::clWhite, Console::clBlack);
	Console::FillRect(' ', 0, 0, Console::Height(), Console::Width());



	// 98. ��������� ������ � �����
	GWarriors->ListSaveToFile(GAppDefaultFileWarrior);
	GGoods->ListSaveToFile(GAppDefaultFileGoods);
	// 99. ������������ ������
	free(GAppDefaultFileGoods);
	free(GAppDefaultFileWarrior);
	free(GAppDefaultDocPath);
	return 0;
}