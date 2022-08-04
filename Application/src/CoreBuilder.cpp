#include "XephEngine/Engine.h"
#include "src/Resources.h"
#include <conio.h>

using namespace xe;

bool UTIL_OVERRIDE = false; // Set to true to skip Utilty Menu
bool DEBUG_MODE = false; // Set to false to disable Debug Window

void RunApplication();
char UtilMenu();
void LoadScenes(Application& app);
void Utility();

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
			Utility();
			break;
		default:
			Debug::Log("Exiting...");
		}
	}
	else
		RunApplication();

	return 0;
}

void RunApplication()
{
	Debug::Setup(DEBUG_MODE);
	Application app;
	LoadScenes(app);
	Debug::Log("Hello World!");
	Debug::LogWarn("I have %i %s", 8, "Apples");
	app.Runtime();
	Debug::ShutDown();
}

char UtilMenu()
{
	std::cout << "   ==== XEPHENGINE UTILITY MENU ====" << std::endl << std::endl;
	std::cout << " [1] - Run Application Build" << std::endl;
	std::cout << " [2] - Utility Options" << std::endl;
	char selection = _getch();
	system("cls");
	return selection;
}

void LoadScenes(Application& app)
{
	app.AddScene(new DefaultScene());
}

void Utility()
{
	system("start XephEngine_Utility.exe");
}