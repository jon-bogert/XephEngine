#include "Scene.h"

xe::Scene::Scene()
{
}

xe::Scene::~Scene()
{
	//delete overlay
	delete world;
}

void xe::Scene::Runtime()
{
    while (Engine::GetWindow()->IsOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) Engine::GetWindow()->Close();
        Engine::GetWindow()->Draw();
    }
}

xe::World* xe::Scene::GetWorld()
{
    return world;
}
