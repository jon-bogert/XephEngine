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
	app.AddState<Triforce>("Triforce");
	app.AddState<Square>("Square");
	app.AddState<Triangle>("Triangle");
	app.Run(config);
}