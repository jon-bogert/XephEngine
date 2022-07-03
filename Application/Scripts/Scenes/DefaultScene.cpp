#include "DefaultScene.h"

// ===== SCENE =====

DefaultScene::DefaultScene()
{
	world = new DefaultWorld();
	//overlay = new DefaultOverlay();
}

// ===== WORLD =====

void DefaultWorld::LoadGameObjects()
{
	AddGameObject(new TestObj());
}

DefaultWorld::DefaultWorld()
	:World(){LoadGameObjects();}
	
// ===== OVERLAY =====
