#include "DefaultScene.h"

// ===== SCENE =====

DefaultScene::DefaultScene()
{
	LoadTextures();
	world = new DefaultWorld();
	//overlay = new DefaultOverlay();
}
void DefaultScene::LoadTextures()
{
	//Note: Files placed in "Assets/Textures/"
	AddTexture("test.png", "test");
}

// ===== WORLD =====

void DefaultWorld::LoadGameObjects()
{
	AddGameObject(new TestObj());
}

DefaultWorld::DefaultWorld()
	:World(){LoadGameObjects();}
	
// ===== OVERLAY =====
