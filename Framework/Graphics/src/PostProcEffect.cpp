#include "Pch.h"
#include "PostProcEffect.h"

#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"
#include "GraphicsSystem.h"

namespace
{
	const char* modeNames[] =
	{
			"None",
			"Monochrome",
			"Invert",
			"Mirror",
			"Blur",
			"Combine2",
			"Motion Blur",
			"Chromatic Aberration",
	};
}

void xe::Graphics::PostProcEffect::Initialize(const std::filesystem::path& filepath)
{
	m_vertexShader.Initialize<VertexPX>(filepath);
	m_pixelShader.Initialize(filepath);

	m_sampler.Initialize(Sampler::Filter::Point, Sampler::AddressMode::Wrap);
	m_postProcBuffer.Initialize();
}

void xe::Graphics::PostProcEffect::Terminate()
{
	m_postProcBuffer.Terminate();
	m_sampler.Terminate();
	m_pixelShader.Terminate();
	m_vertexShader.Terminate();
}

void xe::Graphics::PostProcEffect::Begin()
{
	m_vertexShader.Bind();
	m_pixelShader.Bind();
	m_sampler.BindPixelShader(0);

	for (uint32_t i = 0; i < m_textures.size(); ++i)
	{
		if (m_textures[i])
		{
			m_textures[i]->BindPixelShader(i);
		}
	}

	PostProcData data;
	data.mode = m_mode;

	switch (m_mode)
	{
	case Mode::None:
		break;
	case Mode::Monochrome:
		data.param0 = m_monochromeColor.r;
		data.param1 = m_monochromeColor.g;
		data.param2 = m_monochromeColor.b;
		break;
	case Mode::Invert:
		break;
	case Mode::Mirror:
		data.param0 = m_mirrorScaleX;
		data.param1 = m_mirrorScaleY;
		break;
	case Mode::Blur:
	{
		const uint32_t screenWidth = GraphicsSystem::Get().GetBackBufferWidth();
		const uint32_t screenHeight = GraphicsSystem::Get().GetBackBufferHeight();
		data.param0 = m_blurAmt / screenWidth;
		data.param1 = m_blurAmt / screenHeight;
		break;
	}
	case Mode::Combine2:
		break;
	case Mode::MotionBlur:
		break;
	case Mode::ChromAberr:
		data.param0 = m_chromAbAmt;
		break;
	}
	m_postProcBuffer.Update(data);
	m_postProcBuffer.BindPixelShader(0);
}

void xe::Graphics::PostProcEffect::End()
{
	for (uint32_t i = 0; i < m_textures.size(); ++i)
	{
		m_textures[i]->UnbindPixelShader(i);
	}
}

void xe::Graphics::PostProcEffect::Draw(const RenderObject& renderObj)
{
	renderObj.meshBuffer.Draw();
}

void xe::Graphics::PostProcEffect::SetTexture(const Texture* texture, uint32_t slot)
{
	ASSERT(slot < m_textures.size(), "PostProcEffect -> invalid slot index");
	m_textures[slot] = texture;
}

void xe::Graphics::PostProcEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("Post Processing Effect##", ImGuiTreeNodeFlags_DefaultOpen))
	{
		int currentMode = static_cast<int>(m_mode);
		if (ImGui::Combo("Mode##", &currentMode, modeNames, static_cast<int>(Mode::Count)))
		{
			m_mode = static_cast<Mode>(currentMode);
		}
		ImGui::DragFloat("Mirror Scale X##", &m_mirrorScaleX, 0.1f, -1.f, 1.f);
		ImGui::DragFloat("Mirror Scale Y##", &m_mirrorScaleY, 0.1f, -1.f, 1.f);
		ImGui::ColorEdit3("Monochrome Color##", &m_monochromeColor.r);
		ImGui::DragFloat("Blur Amount##", &m_blurAmt, 1.f, 0.f, 100.f);
		ImGui::DragFloat("Chromatic Aberration Amount##", &m_chromAbAmt, 0.001, 0.0f, 0.01f);
	}
#endif // _DEBUG
}

void xe::Graphics::PostProcEffect::SetMode(const Mode mode)
{
	m_mode = mode;
}
