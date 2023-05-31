#include "Pch.h"
#include "SimpleEffect.h"

#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"
#include "MeshBuffer.h"

using namespace xe::Math;

void xe::Graphics::SimpleEffect::Initialize()
{
	std::filesystem::path filePath = L"../../../Assets/Shaders/DoTexture.fx";
	_vertexShader.Initialize<VertexPX>(filePath);
	_pixelShader.Initialize(filePath);
	_constantBuffer.Initialize(sizeof(Matrix4));
	_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void xe::Graphics::SimpleEffect::Terminate()
{
	_sampler.Terminate();
	_constantBuffer.Terminate();
	_pixelShader.Terminate();
	_vertexShader.Terminate();
}

void xe::Graphics::SimpleEffect::Begin()
{
	_vertexShader.Bind();
	_pixelShader.Bind();
	_constantBuffer.BindVertexShader(0);
	_sampler.BindPixelShader(0);
}

void xe::Graphics::SimpleEffect::Draw(const RenderObject& renderObject)
{
	Matrix4 matWorld = renderObject.transform.Matrix();
	Matrix4 matView = _camera->GetViewMatrix();
	Matrix4 matProj = _camera->GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	_constantBuffer.Update(&wvp);

	renderObject.diffuseTexture.BindPixelShader(0);
	renderObject.meshBuffer.Draw();
}

void xe::Graphics::SimpleEffect::End()
{
	Texture::UnbindPixelShader(0);
}

void xe::Graphics::SimpleEffect::SetCamera(const Camera& camera)
{
	_camera = &camera;
}
