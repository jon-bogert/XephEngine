#include "Pch.h"
#include "Water.h"

void xe::Graphics::Water::Initialize(const Mesh& mesh)
{
	m_mesh = mesh;
}

xe::Graphics::Mesh& xe::Graphics::Water::GetMesh()
{
	return m_mesh;
}
