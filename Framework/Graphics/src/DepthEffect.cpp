#include "Pch.h"
#include "DepthEffect.h"

#include "RenderObject.h"
#include "VertexTypes.h"

namespace stdfs = std::filesystem;

void xe::Graphics::DepthEffect::Initialize(Camera& camera)
{
	_camera = &camera;

	stdfs::path shaderFile = L"../../Assets/Shaders/Depth.fx";
	_vertexShader.Initialize<Vertex>(shaderFile);
	_pixelShader.Initialize(shaderFile);

	_transformBuffer.Initialize();

	constexpr uint32_t depthMapResolution = 4096;
	_depthMapRenderTarget.Initialize(depthMapResolution, depthMapResolution, Texture::Format::RGBA_U32);
}

void xe::Graphics::DepthEffect::Terminate()
{
	_depthMapRenderTarget.Terminate();
	_transformBuffer.Terminate();
	_pixelShader.Terminate();
	_vertexShader.Terminate();
}

void xe::Graphics::DepthEffect::Begin()
{
	_vertexShader.Bind();
	_pixelShader.Bind();
	_transformBuffer.BindVertexShader(0);

	_depthMapRenderTarget.BeginDraw();
}

void xe::Graphics::DepthEffect::End()
{
	_depthMapRenderTarget.EndDraw();
}

void xe::Graphics::DepthEffect::Draw(const RenderObject& renderObj)
{
	const xe::Math::Matrix4& matWorld = renderObj.transform.Matrix();
	const xe::Math::Matrix4& matView = _camera->GetViewMatrix();
	const xe::Math::Matrix4& matProj = _camera->GetProjectionMatrix();

	TransformData data;
	data.wvp = xe::Math::Transpose(matWorld * matView * matProj);
	_transformBuffer.Update(data);

	renderObj.meshBuffer.Draw();
}

void xe::Graphics::DepthEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("Depth", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("Depth Map");
		ImGui::Image(
			_depthMapRenderTarget.GetRawData(),
			{ 144, 144 },
			{ 0, 0 },
			{ 1, 1 },
			{ 1, 1, 1, 1 },
			{ 1, 1, 1, 1 });
	}
#endif // _DEBUG
}
