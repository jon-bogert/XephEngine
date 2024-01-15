#include "Pch.h"
#include "ShadowEffect.h"

#include "RenderObject.h"
#include "VertexTypes.h"

namespace stdfs = std::filesystem;

void xe::Graphics::ShadowEffect::Initialize()
{
	m_lightCamera.SetMode(Camera::ProjectionMode::Orthographic);

	stdfs::path shaderFile = L"../../Assets/Shaders/Shadow.fx";
	m_vertexShader.Initialize<Vertex>(shaderFile);
	m_pixelShader.Initialize(shaderFile);

	m_transformBuffer.Initialize();

	constexpr uint32_t depthMapResolution = 4096;
	m_depthMapRenderTarget.Initialize(depthMapResolution, depthMapResolution, Texture::Format::RGBA_U32);
}

void xe::Graphics::ShadowEffect::Terminate()
{
	m_depthMapRenderTarget.Terminate();
	m_transformBuffer.Terminate();
	m_pixelShader.Terminate();
	m_vertexShader.Terminate();
}

void xe::Graphics::ShadowEffect::Begin()
{
	UpdateLightCamera();

	m_vertexShader.Bind();
	m_pixelShader.Bind();
	m_transformBuffer.BindVertexShader(0);

	m_depthMapRenderTarget.BeginDraw();
}

void xe::Graphics::ShadowEffect::End()
{
	m_depthMapRenderTarget.EndDraw();
}

void xe::Graphics::ShadowEffect::Draw(const RenderObject& renderObj)
{
	const xe::Math::Matrix4& matWorld = renderObj.transform.Matrix();
	const xe::Math::Matrix4& matView = m_lightCamera.GetViewMatrix();
	const xe::Math::Matrix4& matProj = m_lightCamera.GetProjectionMatrix();

	TransformData data;
	data.wvp = xe::Math::Transpose(matWorld * matView * matProj);
	m_transformBuffer.Update(data);

	renderObj.meshBuffer.Draw();
}

void xe::Graphics::ShadowEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("ShadowEffect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("Depth Map");
		ImGui::Image(
			m_depthMapRenderTarget.GetRawData(),
			{ 144, 144 },
			{ 0, 0 },
			{ 1, 1 },
			{ 1, 1, 1, 1 },
			{ 1, 1, 1, 1 });
		ImGui::DragFloat("Size##", &m_size, 1.f, 1.f, 1000.f);
	}
#endif // _DEBUG
}

void xe::Graphics::ShadowEffect::UpdateLightCamera()
{
	ASSERT(m_directionalLight != nullptr, "ShadowEffect -> no light set");

	const xe::Math::Vector3 direction = m_directionalLight->direction;
	m_lightCamera.SetDirection(direction);
	m_lightCamera.SetPosition(m_focalPoint - (direction * 1000.f));
	m_lightCamera.SetNearPlane(1.f);
	m_lightCamera.SetFarPlane(2000.f);
	m_lightCamera.SetSize(m_size, m_size);
}
