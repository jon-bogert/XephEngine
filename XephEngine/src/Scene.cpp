#include "Scene.h"

xe::Scene::Scene()
    :world(nullptr)
{
}

xe::Scene::~Scene()
{
	//delete overlay
	delete world;
}

void xe::Scene::Runtime()
{
    //TODO Call Overlay Start
    world->Start();

    while (Engine::GetWindow()->IsOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) Engine::GetWindow()->Close();
        
        world->Update();

        Engine::GetWindow()->Draw();
    }
}

xe::World* xe::Scene::GetWorld()
{
    return world;
}
