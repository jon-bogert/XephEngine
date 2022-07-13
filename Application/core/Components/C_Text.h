#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class Text : public Component
	{
	protected:
		TextData* text = nullptr;
		std::string fName;
		float size;

	public:
		Text(std::string fontName, float size, GameObject* gameObject);

		void Start();
		void Update();
		sf::Drawable* Draw();

		void SetFont(std::string fontName);
		void SetSize(float size);
		void SetString(const std::string& str);
		void SetColor(const Color color);
		void SetColor(const int r, const int g, const int b);
		void SetColor(const int r, const int g, const int b, const int a);
		void SetOutline(const Color color, const float thickness);
		void SetOutline(const int r, const int g, const int b, const float thickness);
		void SetOutline(const int r, const int g, const int b, const int a, const float thickness);
		void SetLetterSpacing(const float spacing);
		void SetLineSpacing(const float spacing);

		Font* GetFont() const;
		float GetSize() const;
		std::string GetString() const;
		Color GetColor() const;
		Color GetOutlineColor() const;
		float GetOutlineThickness() const;
		float GetLetterSpacing() const;
		float GetLineSpacing() const;

		Vector2 GetOriginOffset() const;
	};
}

