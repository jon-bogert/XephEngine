#include "XephEngine/Engine.h"
#include "src/Resources.h"
#include <conio.h>

using namespace xe;

bool UTIL_OVERRIDE = true; // Set to true to skip Utilty Menu

void RunApplication();
char UtilMenu();
void LoadScenes(Application& app);
void NewComponent();
void NewGameObject();
void NewScene();

int main()
{
	if (!UTIL_OVERRIDE)
	{
		switch (UtilMenu())
		{
		case '1':
			RunApplication();
			break;
		case '2':
			NewComponent();
			break;
		case '3':
			NewGameObject();
			break;
		case '4':
			NewScene();
			break;
		default:
			std::cout << "Exiting...";
		}
	}
	else
		RunApplication();

	return 0;
}

void RunApplication()
{
	Application app;
	LoadScenes(app);
	app.Runtime();
}

char UtilMenu()
{
	std::cout << "   ==== XEPHENGINE UTILITY MENU ====" << std::endl << std::endl;
	std::cout << " [1] - Run Application Build" << std::endl;
	std::cout << " [2] - Create new Component" << std::endl;
	std::cout << " [3] - Create new GameObject" << std::endl;
	std::cout << " [4] - Create new Scene" << std::endl;
	char selection = _getch();
	system("cls");
	return selection;
}

void LoadScenes(Application& app)
{
	app.AddScene(new DefaultScene());
}

void NewComponent()
{
	system("start NewComponent_Utility.exe");
}

void NewGameObject()
{
	system("start NewGameObject_Utility.exe");
}

void NewScene()
{
	system("start NewScene_Utility.exe");
}