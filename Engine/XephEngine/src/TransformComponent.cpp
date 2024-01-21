#include "Pch.h"
#include "TransformComponent.h"

void xe::TransformComponent::DebugUI()
{
	Graphics::SimpleDraw::AddTransfrom(Matrix());
}
