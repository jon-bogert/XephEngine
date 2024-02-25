#pragma once
#include "XephEngine/include/XephEngine.h"


class EditorState : public xe::AppState
{
protected:
	xe::World m_world;

public:


	virtual ~EditorState() {};

	void Initialize() override;
	void Terminate() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
	void DebugUI() override;

protected:
	void UpdateCameraControl(const float& deltaTime);
};