#pragma once
#include "../Libraries.h"
#include "Structs.h"
#include "Font.h"
#

namespace xe
{
	class TextData
	{
		sf::Text* text;

	public:
		TextData(Font* font, float size);
		~TextData();

		sf::Text* UnWrap();

		void SetFont(Font* font);
		void SetSize(float size);
		void SetString(const std::string& str);
		void SetColor(const Color color);
		void SetOutline(const Color color, const float thickness);
		void SetLetterSpacing(const float spacing);
		void SetLineSpacing(const float spacing);

		float GetSize() const;
		std::string GetString() const;
		Color GetColor() const;
		Color GetOutlineColor() const;
		float GetOutlineThickness() const;
		float GetLetterSpacing() const;
		float GetLineSpacing() const;

		Vector2 GetOriginOffset() const;

	private:
		void UpdateOrigin();
	};
}

