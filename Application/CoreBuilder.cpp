#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

void LoadScenes(Application& app);

int main()
{
	Application app;

	LoadScenes(app);
	app.Runtime();

	return 0;
}

void LoadScenes(Application& app)
{
	app.AddScene(new DefaultScene());
}