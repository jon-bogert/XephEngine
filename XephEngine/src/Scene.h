#pragma once
#include "Libraries.h"
#include "Application.h"
#include "World.h"

namespace xe
{
	class World;

	class Scene
	{
	protected:
		World* world;
		//Overlay overlay = nullptr;

	public:
		Scene();
		~Scene();

		void Runtime();

		World* GetWorld();
	};
}

