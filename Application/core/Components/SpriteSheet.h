#pragma once
#include "XephEngine/Engine.h"
#include "../src/Resources.h"

using namespace xe;

class SpriteSheet : public Component
{
protected:
	Sprite* sprite = nullptr;
	std::string textureName;
	Vector2i numCells;
	Vector2i resCells;
	int padding = 0;
	int frame = 0;
	int row = 0;

	bool isAnimated = false;
	//isAnimated
	std::vector<std::string> animationNames;
	std::vector<int> animationLengths;
	int frameRate = 12;
	bool isPaused = false;
	bool absoluteTiming = false;
	float leftOverTiming = 0.f;
	Timer animationTimer;

	//!isAnimated
	std::vector <std::string> cellNames;

public:
	SpriteSheet(std::string textureName, Vector2i numCells, Vector2i resCells, GameObject* gameObject);
	SpriteSheet(std::string textureName, int numCellsWidth, int numCellsHeight, int resCellsX, int resCellsY, GameObject* gameObject);
	~SpriteSheet();

	void Start();
	void Update();
	sf::Drawable* Draw();

	void SetTexture(std::string textureName);
	void UpdateCellResolution(Vector2i newRes);
	void UpdateCellResolution(int newResX, int newResY);

	void SetupAnimated(std::vector<std::string> animNames, std::vector<int> animLengths);
	void SetupNotAnimated(std::vector<std::string> cellNames);

	void SetCell(int index);
	void SetCell(int x, int y);
	void SetCell(Vector2i cell);
	void SetCell(std::string name);
	void NextCell();
	void PrevCell();

	void SetAnimation(int index);
	void SetAnimation(std::string name);
	void NextAnimation();
	void PrevAnimation();
	void SetFrame(int index);
	void NextFrame();
	void PrevFrame();
	void PauseAnimation();
	void PlayAnimation();
	bool GetIsPaused() const;

	void SetFrameRate(const int newRate);
	int GetFrameRate() const;

protected:
	void UpdateFrame();
	bool AnimatedCheck(bool isAnim);
};

