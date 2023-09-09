#include "Pch.h"
#include "Water.h"

void xe::Graphics::Water::Initialize(const Mesh& mesh)
{
	_mesh = mesh;
}

xe::Graphics::Mesh& xe::Graphics::Water::GetMesh()
{
	return _mesh;
}
