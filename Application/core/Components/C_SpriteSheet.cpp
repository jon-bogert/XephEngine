#include "C_SpriteSheet.h"

namespace C
{
	SpriteSheet::SpriteSheet(std::string textureName, Vector2i numCells, Vector2i resCells, GameObject* gameObject)
		:Component(gameObject), textureName(textureName), numCells(numCells), resCells(resCells)
	{
		AddToDrawables();
	}

	SpriteSheet::SpriteSheet(std::string textureName, int numCellsX, int numCellsY, int resCellsX, int resCellsY, GameObject* gameObject)
		:Component(gameObject), textureName(textureName), numCells({ numCellsX, numCellsY }), resCells({ resCellsX, resCellsY })
	{
		AddToDrawables();
	}

	SpriteSheet::~SpriteSheet()
	{
		delete sprite;
	}

	void SpriteSheet::Start()
	{
		SetTexture(textureName);
	}

	void SpriteSheet::Update()
	{
		if (isAnimated && !isPaused)
		{
			if (animationTimer.GetElapsed() >= 1.f / frameRate)
			{
				NextFrame();
				animationTimer.Reset();
			}
		}
	}

	sf::Drawable* SpriteSheet::Draw()
	{
		Draw::SpriteCalc(sprite->UnWrap(), this);
		return sprite->UnWrap();
	}

	void SpriteSheet::SetTexture(std::string textureName)
	{
		if (sprite != nullptr) delete sprite;
		this->textureName = textureName;
		sprite = new Sprite(Engine::GetActiveScene()->FindTexture(textureName));
		sprite->SetFrame(0, 0, resCells.x, resCells.y);
	}

	void SpriteSheet::UpdateCellResolution(Vector2i newRes)
	{
		resCells = newRes;
		sprite->SetFrame(sprite->GetFrame().x, sprite->GetFrame().y, newRes.x, newRes.y);
	}

	void SpriteSheet::UpdateCellResolution(int newResX, int newResY)
	{
		UpdateCellResolution({ newResX, newResY });
	}

	void SpriteSheet::SetupAnimated(std::vector<std::string> animNames, std::vector<int> animLengths)
	{
		if (animNames.size() != numCells.y || animLengths.size() != numCells.y)
		{
			std::cout << "[ERROR] Animantion Names and/or Lengths does not match StriteSheet rows. Unable to create Animations." << std::endl;
			return;
		}

		isAnimated = true;
		animationNames = animNames;
		animationLengths = animLengths;
		animationTimer.Reset();
	}

	void SpriteSheet::SetupNotAnimated(std::vector<std::string> cellNames)
	{
		if (cellNames.size() > (numCells.x * numCells.y))
		{
			std::cout << "[ERROR] SpriteSheet specified cell names is larger than numeber of cells" << std::endl;
			return;
		}

		isAnimated = false;
		this->cellNames = cellNames;
	}

	void SpriteSheet::SetCell(int index)
	{
		if (!AnimatedCheck(false)) return;

		SetCell(Vector2i{ index % numCells.x, index / numCells.x });
	}
	void SpriteSheet::SetCell(int x, int y)
	{
		if (!AnimatedCheck(false)) return;

		SetCell(Vector2i{ x, y });
	}
	void SpriteSheet::SetCell(Vector2i cell)
	{
		if (!AnimatedCheck(false)) return;

		if (cell.x > numCells.x || cell.y > numCells.y)
		{
			std::cout << "[ERROR] SpriteSheet cell out of range." << std::endl;
		}

		frame = cell.x;
		row = cell.y;
		UpdateFrame();
	}

	void SpriteSheet::SetCell(std::string name)
	{
		if (!AnimatedCheck(false)) return;
		if (cellNames.size() == 0)
		{
			std::cout << "[ERROR] SpriteSheet cell names not initialized.";
			return;
		}

		int index{};
		for (std::string n : cellNames)
		{
			if (n == name)
			{
				SetCell(index);
				return;
			}
			index++;
		}
		std::cout << "[ERROR] Couldn't find SpriteSheet cell with name: " << name << std::endl;
	}

	void SpriteSheet::NextCell()
	{
		if (!AnimatedCheck(false)) return;
		if (frame >= numCells.x - 1 && row >= numCells.y - 1)
		{
			SetCell(0, 0);
		}
		else
		{
			SetCell((row * numCells.x) + frame + 1);
		}
	}

	void SpriteSheet::PrevCell()
	{
		if (!AnimatedCheck(false)) return;
		if (frame <= 0 && row <= 0)
		{
			SetCell(numCells.x - 1, numCells.y - 1);
		}
		else
		{
			SetCell((row * numCells.x) + frame - 1);
		}
	}

	void SpriteSheet::SetAnimation(int index)
	{
		if (!AnimatedCheck(true)) return;
		if (index >= numCells.y || index < 0)
		{
			std::cout << "[ERROR] SpriteSheet Animation index out of range";
		}

		row = index;
		frame = 0;
		UpdateFrame();
	}
	void SpriteSheet::SetAnimation(std::string name)
	{
		if (!AnimatedCheck(true)) return;
		int index{};
		for (std::string n : animationNames)
		{
			if (n == name)
			{
				SetAnimation(index);
				return;
			}
			index++;
		}
		std::cout << "[ERROR] Couldn't find SpriteSheet animation with name: " << name << std::endl;
	}
	void SpriteSheet::NextAnimation()
	{
		if (!AnimatedCheck(true)) return;
		if (row >= numCells.y - 1)
		{
			row = 0;
		}
		else
		{
			row = row + 1;
		}
		frame = 0;
		UpdateFrame();
	}
	void SpriteSheet::PrevAnimation()
	{
		if (!AnimatedCheck(true)) return;
		if (row <= 0)
		{
			row = numCells.y - 1;
		}
		else
		{
			row = row - 1;
		}
		frame = 0;
		UpdateFrame();
	}
	void SpriteSheet::SetFrame(int index)
	{
		if (!AnimatedCheck(true)) return;
		if (index >= animationLengths[row])
		{
			std::cout << "[ERROR] SpriteSheet animation frame out of range of current animation";
			return;
		}
		frame = index;
		UpdateFrame();
	}
	void SpriteSheet::NextFrame()
	{
		if (!AnimatedCheck(true)) return;
		if (frame >= animationLengths[row] - 1)
		{
			frame = 0;
		}
		else
		{
			frame += 1;
		}
		UpdateFrame();
	}
	void SpriteSheet::PrevFrame()
	{
		if (!AnimatedCheck(true)) return;
		if (frame <= 0)
		{
			frame = animationLengths[row] - 1;
		}
		else
		{
			frame -= 1;
		}
		UpdateFrame();
	}
	void SpriteSheet::PauseAnimation()
	{
		isPaused = true;
	}
	void SpriteSheet::PlayAnimation()
	{
		isPaused = false;
	}
	bool SpriteSheet::GetIsPaused() const
	{
		return isPaused;
	}

	void SpriteSheet::SetFrameRate(const int newRate)
	{
		frameRate = newRate;
	}

	int SpriteSheet::GetFrameRate() const
	{
		return frameRate;
	}

	// ===== PROTECTED =====

	void SpriteSheet::UpdateFrame()
	{
		sprite->SetFrame(frame * resCells.x + (frame * padding), row * resCells.y + (frame * padding), resCells.x, resCells.y);
	}

	bool SpriteSheet::AnimatedCheck(bool isAnim)
	{
		if (isAnim == isAnimated) return true;

		std::cout << "[ERROR] SpriteSheet 'isAnimated' setting not set properly" << std::endl;
		return false;
	}
}
