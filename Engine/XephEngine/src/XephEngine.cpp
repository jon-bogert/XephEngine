#include "Pch.h"
#include "XephEngine.h"

xe::App& xe::MainApp()
{
	static xe::App app;
	return app;
}