#include "XephEngine/Engine.h"
#include "src/Resources.h"
#include <conio.h>

using namespace xe;

const bool DEBUG_MODE = true; // Set to false to disable Debug Utility and Debug Window

void RunApplication();
void LoadScenes(Application& app);
void RunUtility();

int WinMain()
{
	if (DEBUG_MODE)
	{
		int selection{};
		{
			Utility util;
			selection = util.Runtime();
		}
		switch (selection)
		{
		case 1:
			RunApplication();
			break;
		case 2:
			RunUtility();
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
	app.Runtime();
	Debug::ShutDown();
}

void LoadScenes(Application& app)
{
	app.AddScene(new DefaultScene());
}

void RunUtility()
{
	system("start XephEngine_Utility.exe");
}