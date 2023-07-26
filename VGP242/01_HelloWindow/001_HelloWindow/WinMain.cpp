#include <XephEngine/include/XephEngine.h>

using namespace xe;

class GameState : public AppState
{

};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config =
	{
		L"Hello Window",
		1280, 720
	};

	App app;
	app.AddState<GameState>("GameState");
	app.Run(config);
}