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
	_vertexShader.Initialize<VertexPX>(filepath);
	_pixelShader.Initialize(filepath);

	_sampler.Initialize(Sampler::Filter::Point, Sampler::AddressMode::Wrap);
	_postProcBuffer.Initialize();
}

void xe::Graphics::PostProcEffect::Terminate()
{
	_postProcBuffer.Terminate();
	_sampler.Terminate();
	_pixelShader.Terminate();
	_vertexShader.Terminate();
}

void xe::Graphics::PostProcEffect::Begin()
{
	_vertexShader.Bind();
	_pixelShader.Bind();
	_sampler.BindPixelShader(0);

	for (uint32_t i = 0; i < _textures.size(); ++i)
	{
		if (_textures[i])
		{
			_textures[i]->BindPixelShader(i);
		}
	}

	PPData data;
	data.mode = _mode;

	switch (_mode)
	{
	case Mode::None:
		break;
	case Mode::Monochrome:
		data.param0 = _monochromeColor.r;
		data.param1 = _monochromeColor.g;
		data.param2 = _monochromeColor.b;
		break;
	case Mode::Invert:
		break;
	case Mode::Mirror:
		data.param0 = _mirrorScaleX;
		data.param1 = _mirrorScaleY;
		break;
	case Mode::Blur:
	{
		const uint32_t screenWidth = GraphicsSystem::Get().GetBackBufferWidth();
		const uint32_t screenHeight = GraphicsSystem::Get().GetBackBufferHeight();
		data.param0 = _blurAmt / screenWidth;
		data.param1 = _blurAmt / screenHeight;
		break;
	}
	case Mode::Combine2:
		break;
	case Mode::MotionBlur:
		break;
	case Mode::ChromAberr:
		data.param0 = _chromAbAmt;
		break;
	}
	_postProcBuffer.Update(data);
	_postProcBuffer.BindPixelShader(0);
}

void xe::Graphics::PostProcEffect::End()
{
	for (uint32_t i = 0; i < _textures.size(); ++i)
	{
		_textures[i]->UnbindPixelShader(i);
	}
}

void xe::Graphics::PostProcEffect::Draw(const RenderObject& renderObj)
{
	renderObj.meshBuffer.Draw();
}

void xe::Graphics::PostProcEffect::SetTexture(const Texture* texture, uint32_t slot)
{
	ASSERT(slot < _textures.size(), "PostProcEffect -> invalid slot index");
	_textures[slot] = texture;
}

void xe::Graphics::PostProcEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("Post Processing Effect##", ImGuiTreeNodeFlags_DefaultOpen))
	{
		int currentMode = static_cast<int>(_mode);
		if (ImGui::Combo("Mode##", &currentMode, modeNames, static_cast<int>(Mode::Count)))
		{
			_mode = static_cast<Mode>(currentMode);
		}
		ImGui::DragFloat("Mirror Scale X##", &_mirrorScaleX, 0.1f, -1.f, 1.f);
		ImGui::DragFloat("Mirror Scale Y##", &_mirrorScaleY, 0.1f, -1.f, 1.f);
		ImGui::ColorEdit3("Monochrome Color##", &_monochromeColor.r);
		ImGui::DragFloat("Blur Amount##", &_blurAmt, 1.f, 0.f, 100.f);
		ImGui::DragFloat("Chromatic Aberration Amount##", &_chromAbAmt, 0.001, 0.0f, 0.01f);
	}
#endif // _DEBUG
}

void xe::Graphics::PostProcEffect::SetMode(const Mode mode)
{
	_mode = mode;
}
