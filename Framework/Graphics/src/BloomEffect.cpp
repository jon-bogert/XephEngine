#include "Pch.h"
#include "BloomEffect.h"

#include "Camera.h"
#include "GraphicsSystem.h"
#include "RenderObject.h"
#include "VertexTypes.h"

namespace stdfs = std::filesystem;

void xe::Graphics::BloomEffect::Initialize()
{
	const uint32_t screenWidth = GraphicsSystem::Get().GetBackBufferWidth();
	const uint32_t screenHeight = GraphicsSystem::Get().GetBackBufferHeight();
	_horizontalBlurRenderTarget.Initialize(screenWidth, screenHeight, Texture::Format::RGBA_U8);
	_verticalBlurRenderTarget.Initialize(screenWidth, screenHeight, Texture::Format::RGBA_U8);

	stdfs::path shaderfile = "../../Assets/Shaders/Bloom.fx";
	_vertexShader.Initialize<VertexPX>(shaderfile);
	_horizontalPixelShader.Initialize(shaderfile, "PS_HORIZ");
	_verticalPixelShader.Initialize(shaderfile, "PS_VERT");

	_settingsBuffer.Initialize();
	_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void xe::Graphics::BloomEffect::Terminate()
{
	_sampler.Terminate();
	_settingsBuffer.Terminate();
	_verticalPixelShader.Terminate();
	_horizontalPixelShader.Terminate();
	_verticalBlurRenderTarget.Terminate();
	_horizontalBlurRenderTarget.Terminate();
}

void xe::Graphics::BloomEffect::Begin()
{
	_vertexShader.Bind();
	const uint32_t screenWidth = GraphicsSystem::Get().GetBackBufferWidth();
	const uint32_t screenHeight = GraphicsSystem::Get().GetBackBufferHeight();

	SettingsData data;
	data.width = screenWidth;
	data.height = screenHeight;
	data.multiplier = _blurSaturation;
	_settingsBuffer.Update(data);
	_settingsBuffer.BindPixelShader(0);

	_sampler.BindPixelShader(0);
}

void xe::Graphics::BloomEffect::End()
{
	GraphicsSystem::Get().ResetRenderTarget();
	GraphicsSystem::Get().ResetViewport();
}

void xe::Graphics::BloomEffect::Draw(const RenderObject& renderObject)
{
	_horizontalBlurRenderTarget.BeginDraw();
	_sourceTexture->BindPixelShader(0);
	_horizontalPixelShader.Bind();
	renderObject.meshBuffer.Draw();
	Texture::UnbindPixelShader(0);
	_horizontalBlurRenderTarget.EndDraw();

	for (uint32_t i = 0; i < _blurIterations; ++i)
	{
		_verticalBlurRenderTarget.BeginDraw();
			_horizontalBlurRenderTarget.BindPixelShader(0);
			_verticalPixelShader.Bind();
			renderObject.meshBuffer.Draw();
			Texture::UnbindPixelShader(0);
		_verticalBlurRenderTarget.EndDraw();

		_horizontalBlurRenderTarget.BeginDraw();
			_verticalBlurRenderTarget.BindPixelShader(0);
			_horizontalPixelShader.Bind();
			renderObject.meshBuffer.Draw();
			Texture::UnbindPixelShader(0);
		_horizontalBlurRenderTarget.EndDraw();
	}

	_verticalBlurRenderTarget.BeginDraw();
		_horizontalBlurRenderTarget.BindPixelShader(0);
		_verticalPixelShader.Bind();
		renderObject.meshBuffer.Draw();
		Texture::UnbindPixelShader(0);
	_verticalBlurRenderTarget.EndDraw();
}

void xe::Graphics::BloomEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("Bloom Effect##", ImGuiTreeNodeFlags_DefaultOpen))
	{
		int blurIter = static_cast<int>(_blurIterations);
		if (ImGui::DragInt("Blur Iterations##", &blurIter, 1, 1, 100))
		{
			_blurIterations = static_cast<uint32_t>(blurIter);
		}
		ImGui::DragFloat("Blur Saturation##", &_blurSaturation, 0.001f, 1.f, 10.f);
		ImGui::Text("Horizontal");
		ImGui::Image(_horizontalBlurRenderTarget.GetRawData(), { 144, 144 });
		ImGui::Text("Vertical");
		ImGui::Image(_verticalBlurRenderTarget.GetRawData(), { 144, 144 });
	}
#endif // _DEBUG
}
