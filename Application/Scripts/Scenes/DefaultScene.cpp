#include "DefaultScene.h"

// ===== SCENE =====

DefaultScene::DefaultScene()
{
	LoadTextures();
	LoadFonts();
	world = new DefaultWorld();
	//overlay = new DefaultOverlay();
}
void DefaultScene::LoadTextures()
{
	//Note: Files placed in "Assets/Textures/"
	AddTexture("test.png", "test");
	AddTexture("test-ss.png", "test-ss");
}

void DefaultScene::LoadFonts()
{
	//Note: Files placed in "Assets/Fonts/"
	AddFont("Retro Gaming.ttf", "default");
}

// ===== WORLD =====

void DefaultWorld::LoadGameObjects()
{
	//AddGameObject(new O::FPSCounter());
	AddGameObject(new O::MyTestObj());
	AddGameObject(new O::OtherTestObj());
}

DefaultWorld::DefaultWorld()
	:World(){LoadGameObjects();}
	
// ===== OVERLAY =====
