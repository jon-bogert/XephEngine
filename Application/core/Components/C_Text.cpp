#include "C_Text.h"

namespace C
{
	Text::Text(std::string fontName, float size, GameObject* gameObject)
		:Component(gameObject), fName(fontName), size(size)
	{
		AddToDrawables();
	}

	void Text::Start()
	{
		SetFont(fName);
		SetSize(size);
		SetString("Lorem Ipsum");
	}

	void Text::Update()
	{

	}

	sf::Drawable* Text::Draw()
	{
		Draw::TextCalc(text->UnWrap(), this);
		return text->UnWrap();
	}

	void Text::SetFont(std::string fontName)
	{
		if (text != nullptr) delete text;
		fName = fontName;
		text = new TextData(Engine::GetActiveScene()->FindFont(fName), size);
	}

	void Text::SetSize(float size)
	{
		text->SetSize(size);
	}

	void Text::SetString(const std::string& str)
	{
		text->SetString(str);
	}

	void Text::SetColor(const Color color)
	{
		text->SetColor(color);
	}

	void Text::SetColor(const int r, const int g, const int b)
	{
		SetColor({ r, g, b });
	}

	void Text::SetColor(const int r, const int g, const int b, const int a)
	{
		SetColor({ r, g, b, a });
	}

	void Text::SetOutline(const Color color, const float thickness)
	{
		text->SetOutline(color, thickness);
	}

	void Text::SetOutline(const int r, const int g, const int b, const float thickness)
	{
		SetOutline({ r, g, b }, thickness);
	}

	void Text::SetOutline(const int r, const int g, const int b, const int a, const float thickness)
	{
		SetOutline({ r, g, b, a }, thickness);
	}

	void Text::SetLetterSpacing(const float spacing)
	{
		text->SetLetterSpacing(spacing);
	}

	void Text::SetLineSpacing(const float spacing)
	{
		text->SetLineSpacing(spacing);
	}

	Font* Text::GetFont() const
	{
		return Engine::GetActiveScene()->FindFont(fName);
	}

	float Text::GetSize() const
	{
		return size;
	}

	std::string Text::GetString() const
	{
		return text->GetString();
	}

	Color Text::GetColor() const
	{
		return text->GetColor();
	}

	Color Text::GetOutlineColor() const
	{
		return text->GetOutlineColor();
	}

	float Text::GetOutlineThickness() const
	{
		return text->GetOutlineThickness();
	}

	float Text::GetLetterSpacing() const
	{
		return text->GetLetterSpacing();
	}

	float Text::GetLineSpacing() const
	{
		return text->GetLineSpacing();
	}
	Vector2 Text::GetOriginOffset() const
	{
		float ppu = Engine::GetWindow()->GetPixelsPerUnit();
		return Vector2(text->GetOriginOffset().x * gameObject->transform.scale.x / ppu, text->GetOriginOffset().y * gameObject->transform.scale.y / ppu);
	}
}
