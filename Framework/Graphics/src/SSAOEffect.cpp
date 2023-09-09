#include "Pch.h"
#include "SSAOEffect.h"

#include "RenderObject.h"
#include "VertexTypes.h"

namespace stdfs = std::filesystem;

void xe::Graphics::SSAOEffect::Initialize(Camera& camera, const Texture& depthTexture)
{
	//_camera.SetMode(Camera::ProjectionMode::Perspective);
	_camera = &camera;
	_depthTexture = &depthTexture;

	stdfs::path shaderFile = L"../../Assets/Shaders/SSAO.fx";
	_vertexShader.Initialize<Vertex>(shaderFile);
	_pixelShader.Initialize(shaderFile);

	_transformBuffer.Initialize();
	_settingsBuffer.Initialize();
	_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	constexpr uint32_t depthMapResolution = 4096;
	//_renderTarget.Initialize(depthMapResolution, depthMapResolution, Texture::Format::RGBA_U32);
}

void xe::Graphics::SSAOEffect::Terminate()
{
	//_renderTarget.Terminate();
	_sampler.Terminate();
	_settingsBuffer.Terminate();
	_transformBuffer.Terminate();
	_pixelShader.Terminate();
	_vertexShader.Terminate();
}

void xe::Graphics::SSAOEffect::Begin()
{
	//UpdateCamera();
	SettingsData data;
	data.sampleRadius = _settingsData.sampleRadius;
	data.useSSAO = _settingsData.useSSAO;
	_settingsBuffer.Update(data);
	_settingsBuffer.BindPixelShader(1);

	_vertexShader.Bind();
	_pixelShader.Bind();
	_transformBuffer.BindVertexShader(0);
	_depthTexture->BindPixelShader(0);
	_sampler.BindPixelShader(0);

	//_renderTarget.BeginDraw();
}

void xe::Graphics::SSAOEffect::End()
{
	//_renderTarget.EndDraw();
	_depthTexture->UnbindPixelShader(0);
}

void xe::Graphics::SSAOEffect::Draw(const RenderObject& renderObj)
{
	const xe::Math::Matrix4& matWorld = renderObj.transform.Matrix();
	const xe::Math::Matrix4& matView = _camera->GetViewMatrix();
	const xe::Math::Matrix4& matProj = _camera->GetProjectionMatrix();

	TransformData data;
	data.wvp = xe::Math::Transpose(matWorld * matView * matProj);
	_transformBuffer.Update(data);

	renderObj.meshBuffer.Draw();
}

void xe::Graphics::SSAOEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("SSAO", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Sample Radius$$SSAO", &_settingsData.sampleRadius, 0.01, 0.f, 10.f);
		bool useSSAO = _settingsData.useSSAO != 0;
		ImGui::Checkbox("Use SSAO##", &useSSAO);
		_settingsData.useSSAO = (useSSAO) ? 1 : 0;
	}
#endif // _DEBUG
}
