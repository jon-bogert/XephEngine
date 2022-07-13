#include "TextData.h"
#include "../EngineUtils.h"

xe::TextData::TextData(Font* font, float size)
{
	text = new sf::Text;
	SetFont(font);
}

xe::TextData::~TextData()
{
	delete text;
}

sf::Text* xe::TextData::UnWrap()
{
	return text;
}

void xe::TextData::SetFont(Font* font)
{
	text->setFont(*font->UnWrap());
	UpdateOrigin();
}

void xe::TextData::SetSize(float size)
{
	text->setCharacterSize(size);
	UpdateOrigin();
}

void xe::TextData::SetString(const std::string& str)
{
	text->setString(str);
	UpdateOrigin();
}

void xe::TextData::SetColor(const Color color)
{
	text->setFillColor(Engine::SF_COLOR(color));
}

void xe::TextData::SetOutline(const Color color, const float thickness)
{
	text->setOutlineColor(Engine::SF_COLOR(color));
	text->setOutlineThickness(thickness);
	UpdateOrigin();
}

void xe::TextData::SetLetterSpacing(const float spacing)
{
	text->setLetterSpacing(spacing);
	UpdateOrigin();
}

void xe::TextData::SetLineSpacing(const float spacing)
{
	text->setLineSpacing(spacing);
	UpdateOrigin();
}

float xe::TextData::GetSize() const
{
	return text->getCharacterSize();
}

std::string xe::TextData::GetString() const
{
	return text->getString();
}

xe::Color xe::TextData::GetColor() const
{
	return Engine::SF_COLOR(text->getFillColor());
}

xe::Color xe::TextData::GetOutlineColor() const
{
	return Engine::SF_COLOR(text->getOutlineColor());
}

float xe::TextData::GetOutlineThickness() const
{
	return text->getOutlineThickness();
}

float xe::TextData::GetLetterSpacing() const
{
	return text->getLetterSpacing();
}

float xe::TextData::GetLineSpacing() const
{
	return text->getLineSpacing();
}

xe::Vector2 xe::TextData::GetOriginOffset() const
{
	return Vector2(text->getLocalBounds().width * 0.5f, text->getLocalBounds().height * 0.5f);
}

void xe::TextData::UpdateOrigin()
{
	text->setOrigin(text->getLocalBounds().width * 0.5f, text->getLocalBounds().height * 0.5f);
}


