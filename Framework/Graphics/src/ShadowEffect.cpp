#include "Pch.h"
#include "ShadowEffect.h"

#include "RenderObject.h"
#include "VertexTypes.h"

namespace stdfs = std::filesystem;

void xe::Graphics::ShadowEffect::Initialize()
{
	_lightCamera.SetMode(Camera::ProjectionMode::Orthographic);

	stdfs::path shaderFile = L"../../Assets/Shaders/Shadow.fx";
	_vertexShader.Initialize<Vertex>(shaderFile);
	_pixelShader.Initialize(shaderFile);

	_transformBuffer.Initialize();

	constexpr uint32_t depthMapResolution = 4096;
	_depthMapRenderTarget.Initialize(depthMapResolution, depthMapResolution, Texture::Format::RGBA_U32);
}

void xe::Graphics::ShadowEffect::Terminate()
{
	_depthMapRenderTarget.Terminate();
	_transformBuffer.Terminate();
	_pixelShader.Terminate();
	_vertexShader.Terminate();
}

void xe::Graphics::ShadowEffect::Begin()
{
	UpdateLightCamera();

	_vertexShader.Bind();
	_pixelShader.Bind();
	_transformBuffer.BindVertexShader(0);

	_depthMapRenderTarget.BeginDraw();
}

void xe::Graphics::ShadowEffect::End()
{
	_depthMapRenderTarget.EndDraw();
}

void xe::Graphics::ShadowEffect::Draw(const RenderObject& renderObj)
{
	const xe::Math::Matrix4& matWorld = renderObj.transform.Matrix();
	const xe::Math::Matrix4& matView = _lightCamera.GetViewMatrix();
	const xe::Math::Matrix4& matProj = _lightCamera.GetProjectionMatrix();

	TransformData data;
	data.wvp = xe::Math::Transpose(matWorld * matView * matProj);
	_transformBuffer.Update(data);

	renderObj.meshBuffer.Draw();
}

void xe::Graphics::ShadowEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("ShadowEffect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("Depth Map");
		ImGui::Image(
			_depthMapRenderTarget.GetRawData(),
			{ 144, 144 },
			{ 0, 0 },
			{ 1, 1 },
			{ 1, 1, 1, 1 },
			{ 1, 1, 1, 1 });
		ImGui::DragFloat("Size##", &_size, 1.f, 1.f, 1000.f);
	}
#endif // _DEBUG
}

void xe::Graphics::ShadowEffect::UpdateLightCamera()
{
	ASSERT(_directionalLight != nullptr, "ShadowEffect -> no light set");

	const xe::Math::Vector3 direction = _directionalLight->direction;
	_lightCamera.SetDirection(direction);
	_lightCamera.SetPosition(_focalPoint - (direction * 1000.f));
	_lightCamera.SetNearPlane(1.f);
	_lightCamera.SetFarPlane(2000.f);
	_lightCamera.SetSize(_size, _size);
}
