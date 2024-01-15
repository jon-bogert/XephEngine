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
	m_horizontalBlurRenderTarget.Initialize(screenWidth, screenHeight, Texture::Format::RGBA_U8);
	m_verticalBlurRenderTarget.Initialize(screenWidth, screenHeight, Texture::Format::RGBA_U8);

	stdfs::path shaderfile = "../../Assets/Shaders/Bloom.fx";
	m_vertexShader.Initialize<VertexPX>(shaderfile);
	m_horizontalPixelShader.Initialize(shaderfile, "PS_HORIZ");
	m_verticalPixelShader.Initialize(shaderfile, "PS_VERT");

	m_settingsBuffer.Initialize();
	m_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void xe::Graphics::BloomEffect::Terminate()
{
	m_sampler.Terminate();
	m_settingsBuffer.Terminate();
	m_verticalPixelShader.Terminate();
	m_horizontalPixelShader.Terminate();
	m_verticalBlurRenderTarget.Terminate();
	m_horizontalBlurRenderTarget.Terminate();
}

void xe::Graphics::BloomEffect::Begin()
{
	m_vertexShader.Bind();
	const uint32_t screenWidth = GraphicsSystem::Get().GetBackBufferWidth();
	const uint32_t screenHeight = GraphicsSystem::Get().GetBackBufferHeight();

	SettingsData data;
	data.width = screenWidth;
	data.height = screenHeight;
	data.multiplier = m_blurSaturation;
	m_settingsBuffer.Update(data);
	m_settingsBuffer.BindPixelShader(0);

	m_sampler.BindPixelShader(0);
}

void xe::Graphics::BloomEffect::End()
{
	GraphicsSystem::Get().ResetRenderTarget();
	GraphicsSystem::Get().ResetViewport();
}

void xe::Graphics::BloomEffect::Draw(const RenderObject& renderObject)
{
	m_horizontalBlurRenderTarget.BeginDraw();
	m_sourceTexture->BindPixelShader(0);
	m_horizontalPixelShader.Bind();
	renderObject.meshBuffer.Draw();
	Texture::UnbindPixelShader(0);
	m_horizontalBlurRenderTarget.EndDraw();

	for (uint32_t i = 0; i < m_blurIterations; ++i)
	{
		m_verticalBlurRenderTarget.BeginDraw();
			m_horizontalBlurRenderTarget.BindPixelShader(0);
			m_verticalPixelShader.Bind();
			renderObject.meshBuffer.Draw();
			Texture::UnbindPixelShader(0);
		m_verticalBlurRenderTarget.EndDraw();

		m_horizontalBlurRenderTarget.BeginDraw();
			m_verticalBlurRenderTarget.BindPixelShader(0);
			m_horizontalPixelShader.Bind();
			renderObject.meshBuffer.Draw();
			Texture::UnbindPixelShader(0);
		m_horizontalBlurRenderTarget.EndDraw();
	}

	m_verticalBlurRenderTarget.BeginDraw();
		m_horizontalBlurRenderTarget.BindPixelShader(0);
		m_verticalPixelShader.Bind();
		renderObject.meshBuffer.Draw();
		Texture::UnbindPixelShader(0);
	m_verticalBlurRenderTarget.EndDraw();
}

void xe::Graphics::BloomEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("Bloom Effect##", ImGuiTreeNodeFlags_DefaultOpen))
	{
		int blurIter = static_cast<int>(m_blurIterations);
		if (ImGui::DragInt("Blur Iterations##", &blurIter, 1, 1, 100))
		{
			m_blurIterations = static_cast<uint32_t>(blurIter);
		}
		ImGui::DragFloat("Blur Saturation##", &m_blurSaturation, 0.001f, 1.f, 10.f);
		ImGui::Text("Horizontal");
		ImGui::Image(m_horizontalBlurRenderTarget.GetRawData(), { 144, 144 });
		ImGui::Text("Vertical");
		ImGui::Image(m_verticalBlurRenderTarget.GetRawData(), { 144, 144 });
	}
#endif // _DEBUG
}
