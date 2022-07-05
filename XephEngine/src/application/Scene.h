#pragma once
#include "../Libraries.h"
#include "../../lib/XephEngine/Engine.h"

namespace xe
{
	class World;
	struct Transform;

	class Scene
	{
	protected:
		World* world;
		//Overlay overlay = nullptr;

		Transform camera;
		std::map<std::string, Texture*> textures;
		std::map<std::string, Font*> fonts;


	public:
		Scene();
		~Scene();

		void Runtime();

		World* GetWorld();
		//Overlay* GetOverlay
		Transform& GetCamera(); // TODO Swicth to public

		void AddTexture(const std::string fileName, const std::string name);
		Texture* FindTexture(const std::string name);

		void AddFont(const std::string fileName, const std::string name);
		Font* FindFont(const std::string name);

	protected:
		virtual void LoadTextures();
		virtual void LoadFonts();
	};
}

