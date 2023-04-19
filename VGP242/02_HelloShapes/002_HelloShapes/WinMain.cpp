#include <XephEngine/include/XephEngine.h>
#include "GameState.h"
#include "Shapes.h"

using namespace xe;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config =
	{
		L"Hello Window",
		1280, 720
	};

	App& app = MainApp();
	app.AddState<Triangle>("Triangle");
	app.AddState<Square>("Square");
	app.Run(config);
}