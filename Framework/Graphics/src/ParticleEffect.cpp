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
	m_vertexShader.Initialize<VertexPC>(filepath);
	m_pixelShader.Initialize(filepath);
	m_transformBuffer.Initialize();
	m_blendState.Initialize(BlendState::Mode::AlphaBlend);
}

void xe::Graphics::ParticleEffect::Terminate()
{
	m_blendState.Terminate();
	m_transformBuffer.Terminate();
	m_pixelShader.Terminate();
	m_vertexShader.Terminate();
}

void xe::Graphics::ParticleEffect::Begin()
{
	m_vertexShader.Bind();
	m_pixelShader.Bind();
	m_transformBuffer.BindVertexShader(0);
	m_blendState.Set();
}

void xe::Graphics::ParticleEffect::End()
{
	m_blendState.Clear();
}

void xe::Graphics::ParticleEffect::Draw(const RenderObject& renderObj)
{
	Matrix4 matWorld = renderObj.transform.Matrix();
	Matrix4 matView = m_camera->GetViewMatrix();
	Matrix4 matProj = m_camera->GetProjectionMatrix();

	Matrix4 matFinal = matWorld * matView * matProj;
	TransformData data;
	data.wvp = Transpose(matFinal);
	m_transformBuffer.Update(data);

	renderObj.meshBuffer.Draw();
}

void xe::Graphics::ParticleEffect::DebugUI()
{
}

void xe::Graphics::ParticleEffect::SetCamera(const Camera& camera)
{
	m_camera = &camera;
}
