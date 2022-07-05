#include "Scene.h"

xe::Scene::Scene()
    :world(nullptr)
{
}

xe::Scene::~Scene()
{
	//delete overlay
    for (std::pair<std::string, Texture*> t : textures)
    {
        delete t.second;
    }
    for (std::pair<std::string, Font*> f : fonts)
    {
        delete f.second;
    }
	delete world;
}

void xe::Scene::Runtime()
{
    //TODO Call Overlay Start
    world->Start();

    while (Engine::GetWindow()->IsOpen())
    {
        Time::UpdateDelta();

        InputSystem::Update();
        if (InputSystem::CloseWindow()) Engine::GetWindow()->Close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) Engine::GetWindow()->Close();
        
        world->Update();
        //TODO Call Overlay Draw
        Engine::GetWindow()->Draw();
    }
}

xe::World* xe::Scene::GetWorld()
{
    return world;
}

xe::Transform& xe::Scene::GetCamera()
{
    return camera;
}

void xe::Scene::AddTexture(const std::string fileName, const std::string name)
{
    std::string path = "Assets/Textures/";
    path.append(fileName);
    textures.insert({ name, new Texture(path) });
}

xe::Texture* xe::Scene::FindTexture(const std::string name)
{
    return textures[name];
}

void xe::Scene::AddFont(const std::string fileName, const std::string name)
{
    std::string path = "Assets/Fonts/";
    path.append(fileName);
    fonts.insert({ name, new Font(path) });
}

xe::Font* xe::Scene::FindFont(const std::string name)
{
    return fonts[name];
}

// ===== PROTECTED =====

void xe::Scene::LoadTextures()
{
}

void xe::Scene::LoadFonts()
{
}
