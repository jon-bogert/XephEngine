#include "Pch.h"
#include "CameraService.h"

#include "CameraComponent.h"

void xe::CameraService::DebugUI()
{
	Graphics::SimpleDraw::Draw(Main());
}

const Graphics::Camera& xe::CameraService::Main() const
{
	ASSERT(m_mainCamera != nullptr, "CameraService: has no main camera");
	return m_mainCamera->GetCamera();
}

void xe::CameraService::SetMainCamera(const uint32_t index)
{
	if (index >= m_cameraEntries.size())
		return;
	m_mainCamera = m_cameraEntries[index];
}

void xe::CameraService::Register(const CameraComponent* cameraComponent)
{
	m_cameraEntries.push_back(cameraComponent);
	if (m_mainCamera == nullptr)
		m_mainCamera = cameraComponent;
}

void xe::CameraService::Unregister(const CameraComponent* cameraComponent)
{
	auto iter = std::find(m_cameraEntries.begin(), m_cameraEntries.end(), cameraComponent);
	if (iter != m_cameraEntries.end())
	{
		if (m_mainCamera == *iter)
		{
			m_mainCamera = nullptr;
		}
		m_cameraEntries.erase(iter);
		if (m_mainCamera == nullptr && !m_cameraEntries.empty())
		{
			m_mainCamera = m_cameraEntries.front();
		}
	}
}
