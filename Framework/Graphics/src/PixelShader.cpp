#include "Pch.h"
#include "PixelShader.h"
#include "GraphicsSystem.h"

void xe::Graphics::PixelShader::Initialize(const std::filesystem::path& filePath)
{
	ID3D11Device* device = GraphicsSystem::Get().GetDevice();

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	HRESULT hResult = D3DCompileFromFile(
		filePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS", "ps_5_0",
		shaderFlags, 0,
		&shaderBlob,
		&errorBlob
	);
	if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		LOG("%s", static_cast<const char*> (errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hResult), "Failed to compile pixel shader");

	hResult = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&_pixelShader
	);
	ASSERT(SUCCEEDED(hResult), "Failed to create pixel shader");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
}

void xe::Graphics::PixelShader::Terminate()
{
	SafeRelease(_pixelShader);
}

void xe::Graphics::PixelShader::Bind()
{
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();
	context->PSSetShader(_pixelShader, nullptr, 0);
}
