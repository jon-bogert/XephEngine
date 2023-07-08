#include "Pch.h"
#include "StandardEffect.h"
#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace xe;
using namespace xe::Math;

void xe::Graphics::StandardEffect::Initialize(const std::filesystem::path& path)
{
	_transformBuffer.Initialize(sizeof(Matrix4));
	_vertexShader.Initialize<Vertex>(path);
	_pixelShader.Initialize(path);
	_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void xe::Graphics::StandardEffect::Terminate()
{
	_sampler.Terminate();
	_pixelShader.Terminate();
	_vertexShader.Terminate();
	_transformBuffer.Terminate();
}

void xe::Graphics::StandardEffect::Begin()
{
	ASSERT(_camera, "Standard Effect -> no camera set");

	_vertexShader.Bind();
	_pixelShader.Bind();

	_transformBuffer.BindVertexShader(0);
	
	_sampler.BindVertexShader(0);
	_sampler.BindPixelShader(0);
}

void xe::Graphics::StandardEffect::End()
{
}

void xe::Graphics::StandardEffect::Draw(const RenderObject& renderObject)
{
	const Matrix4& matWorld = renderObject.transform.Matrix();
	const Matrix4& matView = _camera->GetViewMatrix();
	const Matrix4& matProj = _camera->GetProjectionMatrix();

	Matrix4 matFinal = Transpose(matWorld * matView * matProj);
	_transformBuffer.Update(&matFinal);

	TextureManager::BindPixelShader(renderObject.diffuseMapID, 0);

	renderObject.meshBuffer.Draw();
}

void xe::Graphics::StandardEffect::SetCamera(const Camera& camera)
{
	_camera = &camera;
}

void xe::Graphics::StandardEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("Standard##Effect", ImGuiTreeNodeFlags_DefaultOpen))
	{

	}
#endif
}
