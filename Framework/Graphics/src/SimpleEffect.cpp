#include "Pch.h"
#include "SimpleEffect.h"

#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"
#include "MeshBuffer.h"
#include "TextureManager.h"

using namespace xe::Math;

void xe::Graphics::SimpleEffect::Initialize()
{
	std::filesystem::path filePath = L"../../Assets/Shaders/DoTexture.fx";
	m_vertexShader.Initialize<VertexPX>(filePath);
	m_pixelShader.Initialize(filePath);
	m_constantBuffer.Initialize(sizeof(Matrix4));
	m_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void xe::Graphics::SimpleEffect::Terminate()
{
	m_sampler.Terminate();
	m_constantBuffer.Terminate();
	m_pixelShader.Terminate();
	m_vertexShader.Terminate();
}

void xe::Graphics::SimpleEffect::Begin()
{
	m_vertexShader.Bind();
	m_pixelShader.Bind();
	m_constantBuffer.BindVertexShader(0);
	m_sampler.BindPixelShader(0);
}

void xe::Graphics::SimpleEffect::Draw(const RenderObject& renderObject)
{
	Matrix4 matWorld = renderObject.transform.Matrix();
	Matrix4 matView = m_camera->GetViewMatrix();
	Matrix4 matProj = m_camera->GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	m_constantBuffer.Update(&wvp);

	TextureManager::BindPixelShader(renderObject.diffuseMapID, 0);

	renderObject.meshBuffer.Draw();
}

void xe::Graphics::SimpleEffect::End()
{
	Texture::UnbindPixelShader(0);
}

void xe::Graphics::SimpleEffect::SetCamera(const Camera& camera)
{
	m_camera = &camera;
}
