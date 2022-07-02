#pragma once
#include "XephEngine/Engine.h"
#include "../../src/Resources.h"

using namespace xe;

class DefaultWorld;

class DefaultScene : public Scene
{
protected:
	DefaultWorld* world;
	//NewOverlay* overlay;

public:
	DefaultScene();
	~DefaultScene();

};

