#include <XephEngine/include/XephEngine.h>
#include "GameState.h"
#include "EditorState.h"
#include "EditPrefabState.h"

using namespace xe;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config =
	{
		L"Hello Window",
		1280, 720
	};

	App& app = MainApp();
	app.AddState<GameState>("GameState");
	app.AddState<EditorState>("EditorState");
	app.AddState<EditPrefabState>("EditPrefabState");
	app.Run(config);
}