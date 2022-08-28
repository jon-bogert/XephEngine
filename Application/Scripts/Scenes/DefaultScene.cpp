#include "DefaultScene.h"

// ===== SCENE =====

DefaultScene::DefaultScene()
{
	LoadTextures();
	LoadFonts();
	LoadAudio();
	world = new DefaultWorld();
	//overlay = new DefaultOverlay();
}
void DefaultScene::LoadTextures()
{
	//Note: Files placed in "Assets/Textures/"
	AddTexture("test.png", "test");
	AddTexture("test-ss.png", "test-ss");
	AddTexture("test-circle.png", "test-circle");
}

void DefaultScene::LoadFonts()
{
	//Note: Files placed in "Assets/Fonts/"
	AddFont("PixelSplitter-Bold.ttf", "default");
}

void DefaultScene::LoadAudio()
{
	//Note: Files placed in "Assets/Audio/"
}

// ===== WORLD =====

void DefaultWorld::LoadGameObjects()
{
	AddGameObject(new O::PhysicsCore());
	AddGameObject(new O::FPSCounter());
	AddGameObject(new O::Ground());
	AddGameObject(new O::Box0());
	AddGameObject(new O::Box1());
}

DefaultWorld::DefaultWorld()
	:World(){LoadGameObjects();}
	
// ===== OVERLAY =====
