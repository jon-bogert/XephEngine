#include "Pch.h"
#include "Texture.h"

#include "GraphicsSystem.h"
#include <DirectXTK/Inc/WICTextureLoader.h>

void xe::Graphics::Texture::UnbindPixelShader(uint32_t slot)
{
	static ID3D11ShaderResourceView* dummy = nullptr;
	GraphicsSystem::Get().GetContext()->PSSetShaderResources(slot, 1, &dummy);
}

xe::Graphics::Texture::~Texture()
{
	ASSERT(_shaderResourceView == nullptr, "Texture: terminate must be called before destruction");
}

xe::Graphics::Texture::Texture(Texture&& other) noexcept
	: _shaderResourceView(other._shaderResourceView)
{
	other._shaderResourceView = nullptr;
}

xe::Graphics::Texture& xe::Graphics::Texture::operator=(Texture&& other) noexcept
{
	_shaderResourceView = other._shaderResourceView;
	other._shaderResourceView = nullptr;
	return *this;
}

void xe::Graphics::Texture::Initialize(const std::filesystem::path& fileName)
{
	ID3D11Device* device = GraphicsSystem::Get().GetDevice();
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();
	HRESULT hResult = DirectX::CreateWICTextureFromFile(device, context, fileName.c_str(), nullptr, &_shaderResourceView);
	ASSERT(SUCCEEDED(hResult), "Texture: failed to create texture %ls", fileName.c_str());
}

void xe::Graphics::Texture::Initialize(uint32_t width, uint32_t height, Format format)
{
	ASSERT(false, "Texture: not yet implemented for base Texture class");
}

void xe::Graphics::Texture::Terminate()
{
	SafeRelease(_shaderResourceView);
}

void xe::Graphics::Texture::BindVertexShader(uint32_t slot) const
{
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();
	context->VSSetShaderResources(slot, 1, &_shaderResourceView);
}

void xe::Graphics::Texture::BindPixelShader(uint32_t slot) const
{
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();
	context->PSSetShaderResources(slot, 1, &_shaderResourceView);
}

DXGI_FORMAT xe::Graphics::Texture::GetDXGIFormat(Format format)
{
	switch (format)
	{
	case Format::RGBA_U8: return DXGI_FORMAT_R8G8B8A8_UNORM;
	case Format::RGBA_U32: return DXGI_FORMAT_R32G32B32A32_UINT;
	default:
		break;
	}
	return DXGI_FORMAT_R8G8B8A8_UNORM;
}
