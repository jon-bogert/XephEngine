#pragma once
#include "Libraries.h"
#include "Application.h"
#include "World.h"
#include "Texture.h"

namespace xe
{
	class World;

	class Scene
	{
	protected:
		World* world;
		//Overlay overlay = nullptr;

		Transform camera;
		std::map<Texture*, std::string> textures;


	public:
		Scene();
		~Scene();

		void Runtime();

		World* GetWorld();
		//Overlay* GetOverlay
		Transform& GetCamera(); // TODO Swicth to public

		void AddTexture(const std::string fileName, const std::string name);
		Texture* FindTexture(const std::string name);

	protected:
		virtual void LoadTextures();
	};
}

