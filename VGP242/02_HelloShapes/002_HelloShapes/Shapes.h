#pragma once
#include "GameState.h"

class Triangle : public GameState
{
protected:
	void CreateShape() override;

public:
	void Update(const float& deltaTime) override;
};

class Square : public GameState
{
protected:
	void CreateShape() override;

public:
	void Update(const float& deltaTime) override;
};