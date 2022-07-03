#pragma once
#include "XephEngine/Engine.h"
#include "../src/Resources.h"

using namespace xe;

// ===== SCENE =====
 
class DefaultScene : public Scene
{
public:
	DefaultScene();
protected:
	void LoadTextures();
};

// ===== WORLD =====

class DefaultWorld : public World
{
protected:
	void LoadGameObjects();
	
public:
	DefaultWorld();
};

// ===== OVERLAY =====

