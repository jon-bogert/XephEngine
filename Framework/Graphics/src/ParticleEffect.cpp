#include "Pch.h"
#include "ParticleEffect.h"

#include "Camera.h"
#include "RenderObject.h"
#include "MeshBuffer.h"
#include "VertexTypes.h"

using namespace xe::Math;
namespace stdfs = std::filesystem;

void xe::Graphics::ParticleEffect::Initialize()
{
	stdfs::path filepath = L"../../Assets/Shaders/DoParticle.fx";
	_vertexShader.Initialize<VertexPC>(filepath);
	_pixelShader.Initialize(filepath);
	_transformBuffer.Initialize();
	_blendState.Initialize(BlendState::Mode::AlphaBlend);
}

void xe::Graphics::ParticleEffect::Terminate()
{
	_blendState.Terminate();
	_transformBuffer.Terminate();
	_pixelShader.Terminate();
	_vertexShader.Terminate();
}

void xe::Graphics::ParticleEffect::Begin()
{
	_vertexShader.Bind();
	_pixelShader.Bind();
	_transformBuffer.BindVertexShader(0);
	_blendState.Set();
}

void xe::Graphics::ParticleEffect::End()
{
	_blendState.Clear();
}

void xe::Graphics::ParticleEffect::Draw(const RenderObject& renderObj)
{
	Matrix4 matWorld = renderObj.transform.Matrix();
	Matrix4 matView = _camera->GetViewMatrix();
	Matrix4 matProj = _camera->GetProjectionMatrix();

	Matrix4 matFinal = matWorld * matView * matProj;
	TransformData data;
	data.wvp = Transpose(matFinal);
	_transformBuffer.Update(data);

	renderObj.meshBuffer.Draw();
}

void xe::Graphics::ParticleEffect::DebugUI()
{
}

void xe::Graphics::ParticleEffect::SetCamera(const Camera& camera)
{
	_camera = &camera;
}
