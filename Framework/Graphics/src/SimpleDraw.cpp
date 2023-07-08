#include "Pch.h"
#include "SimpleDraw.h"

#include "BlendState.h"
#include "Camera.h"
#include "ConstantBuffer.h"
#include "MeshBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "VertexTypes.h"

using namespace xe;
using namespace xe::Graphics;
using namespace xe::Math;

namespace
{
	class _SimpleDraw
	{
		VertexShader _vertexShader;
		PixelShader _pixelShader;
		ConstantBuffer _constantBuffer;
		MeshBuffer _meshBuffer;
		BlendState _blendState;

		std::unique_ptr<VertexPC[]> _lineVertices;
		std::unique_ptr<VertexPC[]> _faceVertices;
		uint32_t _lineVertexCount = 0;
		uint32_t _faceVertexCount = 0;
		uint32_t _maxVertexCount = 0;

	public:
		void Initialize(uint32_t maxVertexCount)
		{
			std::filesystem::path shaderFile = L"../../Assets/Shaders/SimpleDraw.fx";
			_vertexShader.Initialize<VertexPC>(shaderFile);
			_pixelShader.Initialize(shaderFile);
			_constantBuffer.Initialize(sizeof(Matrix4));
			_meshBuffer.Initialize(nullptr, sizeof(VertexPC), maxVertexCount);
			_blendState.Initialize(BlendState::Mode::AlphaBlend);

			_lineVertices = std::make_unique<VertexPC[]>(maxVertexCount);
			_faceVertices = std::make_unique<VertexPC[]>(maxVertexCount);
			_lineVertexCount = 0;
			_faceVertexCount = 0;
			_maxVertexCount = maxVertexCount;
		}
		void Terminate()
		{
			_blendState.Terminate();
			_meshBuffer.Terminate();
			_constantBuffer.Terminate();
			_pixelShader.Terminate();
			_vertexShader.Terminate();
		}
		void Draw(const Camera& camera)
		{
			Matrix4 matView = camera.GetViewMatrix();
			Matrix4 matProj = camera.GetProjectionMatrix();
			Matrix4 transform = Transpose(matView * matProj);

			_constantBuffer.Update(&transform);
			_constantBuffer.BindVertexShader(0);

			_vertexShader.Bind();
			_pixelShader.Bind();

			_blendState.Set();

			_meshBuffer.Update(_faceVertices.get(), _faceVertexCount);
			_meshBuffer.SetTopology(MeshBuffer::Topology::Triangles);
			_meshBuffer.Draw();

			_meshBuffer.Update(_lineVertices.get(), _lineVertexCount);
			_meshBuffer.SetTopology(MeshBuffer::Topology::Lines);
			_meshBuffer.Draw();

			BlendState::Clear();

			_lineVertexCount = 0;
			_faceVertexCount = 0;
		}

		void AddLine(const Vector3& v0, const Vector3& v1, const Color& color)
		{
			if (_lineVertexCount + 2 <= _maxVertexCount)
			{
				_lineVertices[_lineVertexCount++] = VertexPC{ v0, color };
				_lineVertices[_lineVertexCount++] = VertexPC{ v1, color };
			}
		}
		void AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Color& color)
		{
			if (_faceVertexCount + 2 <= _maxVertexCount)
			{
				_faceVertices[_faceVertexCount++] = VertexPC{ v0, color };
				_faceVertices[_faceVertexCount++] = VertexPC{ v1, color };
				_faceVertices[_faceVertexCount++] = VertexPC{ v2, color };
			}
		}
	};

	std::unique_ptr<_SimpleDraw> _inst;
}

void xe::Graphics::SimpleDraw::Initialize(uint32_t maxVertexCount)
{
	_inst = std::make_unique<_SimpleDraw>();
	_inst->Initialize(maxVertexCount);
}

void xe::Graphics::SimpleDraw::Terminate()
{
	_inst->Terminate();
	_inst.reset();
}

void xe::Graphics::SimpleDraw::Draw(const Camera& camera)
{
	_inst->Draw(camera);
}

void xe::Graphics::SimpleDraw::AddLine(const xe::Math::Vector3& v0, const xe::Math::Vector3& v1, const xe::Color& color)
{
	_inst->AddLine(v0, v1, color);
}

void xe::Graphics::SimpleDraw::AddFace(const xe::Math::Vector3& v0, const xe::Math::Vector3& v1, const xe::Math::Vector3& v2, const xe::Color& color)
{
	_inst->AddFace(v0, v1, v2, color);
}

void xe::Graphics::SimpleDraw::AddBoxWireframe(const xe::Math::Vector3& min, const xe::Math::Vector3& max, const xe::Color& color)
{
	AddBoxWireframe(min.x, min.y, min.z, max.x, max.y, max.z, color);
}

void xe::Graphics::SimpleDraw::AddBoxWireframe(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const xe::Color& color)
{
	const Vector3 trf = { maxX, maxY, minZ };
	const Vector3 brf = { maxX, minY, minZ };
	const Vector3 tlf = { minX, maxY, minZ };
	const Vector3 blf = { minX, minY, minZ };

	const Vector3 trb = { maxX, maxY, maxZ };
	const Vector3 brb = { maxX, minY, maxZ };
	const Vector3 tlb = { minX, maxY, maxZ };
	const Vector3 blb = { minX, minY, maxZ };

	//Front
	AddLine(trf, brf, color);
	AddLine(brf, blf, color);
	AddLine(blf, tlf, color);
	AddLine(tlf, trf, color);

	//Back
	AddLine(trb, brb, color);
	AddLine(brb, blb, color);
	AddLine(blb, tlb, color);
	AddLine(tlb, trb, color);

	//Top
	AddLine(trb, trf, color);
	AddLine(tlb, tlf, color);

	//Bottom
	AddLine(brb, brf, color);
	AddLine(blb, blf, color);
}

void xe::Graphics::SimpleDraw::AddBoxFilled(const xe::Math::Vector3& min, const xe::Math::Vector3& max, const xe::Color& color)
{
	AddBoxFilled(min.x, min.y, min.z, max.x, max.y, max.z, color);
}

void xe::Graphics::SimpleDraw::AddBoxFilled(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const xe::Color& color)
{
	const Vector3 trf = { maxX, maxY, minZ };
	const Vector3 brf = { maxX, minY, minZ };
	const Vector3 tlf = { minX, maxY, minZ };
	const Vector3 blf = { minX, minY, minZ };

	const Vector3 trb = { maxX, maxY, maxZ };
	const Vector3 brb = { maxX, minY, maxZ };
	const Vector3 tlb = { minX, maxY, maxZ };
	const Vector3 blb = { minX, minY, maxZ };

	//Front
	AddFace(trf, brf, blf, color);
	AddFace(trf, blf, tlf, color);

	//Back
	AddFace(trb, blb, brb, color);
	AddFace(trb, tlb, blb, color);

	//Top
	AddFace(trb, trf, tlf, color);
	AddFace(trb, tlf, tlb, color);

	//Bottom
	AddFace(brb, blf, brf, color);
	AddFace(brb, blb, blf, color);

	//Right
	AddFace(trb, brb, brf, color);
	AddFace(trb, brf, trf, color);

	//Left
	AddFace(tlb, blf, blb, color);
	AddFace(tlb, tlf, blf, color);
}

void xe::Graphics::SimpleDraw::AddSphere(uint32_t slices, uint32_t rings, float radius, const Color& color)
{
	Vector3 v0 = Vector3::Zero;
	Vector3 v1 = Vector3::Zero;

	float vertRotation = (Math::Const::Pi / static_cast<float>(rings - 1));
	float horizRotation = (Math::Const::TwoPi / static_cast<float>(slices));

	for (uint32_t ring = 0; ring < rings; ++ring)
	{
		float rPos0 = static_cast<float>(ring);
		float phi0 = rPos0 * vertRotation;
		float rPos1 = static_cast<float>(ring + 1);
		float phi1 = rPos1 * vertRotation;
		for (uint32_t slice = 0; slice <= slices; ++slice)
		{
			float sPos0 = static_cast<float>(slice);
			float rotation0 = sPos0 * horizRotation;

			float sPos1 = static_cast<float>(slice + 1);
			float rotation1 = sPos1 * horizRotation;

			v0 = {
					radius * sin(rotation0) * sin(phi0),
					radius * cos(phi0),
					radius * cos(rotation0) * sin(phi0)
			};

			v1 = {
					radius * sin(rotation1) * sin(phi0),
					radius * cos(phi0),
					radius * cos(rotation1) * sin(phi0)
			};

			AddLine(v0, v1, color);

			v1 = {
					radius * sin(rotation0) * sin(phi1),
					radius * cos(phi1),
					radius * cos(rotation0) * sin(phi1)
			};

			AddLine(v0, v1, color);
		}
	}
}

void xe::Graphics::SimpleDraw::AddGroundPlane(float size, const Color& color)
{
	const float halfSize = size * 0.5f;
	const uint32_t intSize = static_cast<uint32_t>(size);

	for (uint32_t i = 0; i <= intSize; ++i)
	{
		AddLine({ i - halfSize, 0.f, -halfSize }, { i - halfSize, 0.f, halfSize }, color);
		AddLine({ -halfSize, 0.f, i - halfSize}, { halfSize, 0.f, i - halfSize }, color);
	}
}

void xe::Graphics::SimpleDraw::AddGroundCircle(uint32_t slices, float radius, const xe::Color& color)
{
	Vector3 v0 = Vector3::Zero;
	Vector3 v1 = Vector3::Zero;
	float horizRotation = (Math::Const::TwoPi / static_cast<float>(slices));
	for (uint32_t s = 0; s <= slices; ++s)
	{
		float slice0 = static_cast<float>(s);
		float rotation0 = slice0 * horizRotation;
		float slice1 = static_cast<float>(s + 1);
		float rotation1 = slice1 * horizRotation;
		v0 = { radius * std::sin(rotation0), 0.f, radius * std::cos(rotation0) };
		v1 = { radius * std::sin(rotation1), 0.f, radius * std::cos(rotation1) };
		AddLine(v0, v1, color);
	}
}

void xe::Graphics::SimpleDraw::AddTransfrom(const xe::Math::Matrix4& matrix)
{
	const Vector3 side = { matrix._11, matrix._12, matrix._13 };
	const Vector3 up = { matrix._21, matrix._22, matrix._23 };
	const Vector3 fwd = { matrix._31, matrix._32, matrix._33 };
	const Vector3 pos = { matrix._41, matrix._42, matrix._43 };

	AddLine(pos, pos + side, Colors::Red);
	AddLine(pos, pos + up, Colors::Green);
	AddLine(pos, pos + fwd, Colors::Blue);
}
