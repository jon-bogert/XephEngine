#include "Pch.h"
#include "Camera.h"

#include "GraphicsSystem.h"

using namespace xe;
using namespace xe::Graphics;

void Camera::SetMode(ProjectionMode mode)
{
	m_projectionMode = mode;
}

void Camera::SetPosition(const xe::Math::Vector3& position)
{
	m_position = position;
}

void Camera::SetDirection(const xe::Math::Vector3& direction)
{
	// Prevent setting direction straight up or down
	auto dir = xe::Math::Normalize(direction);
	if (xe::Math::Abs(xe::Math::Dot(dir, xe::Math::Vector3::YAxis)) < 0.995f)
		m_direction = dir;
}

void Camera::SetLookAt(const xe::Math::Vector3& target)
{
	SetDirection(target - m_position);
}

void Camera::SetFov(float fov)
{
	constexpr float kMinFov = 10.0f * xe::Math::Const::DegToRad;
	constexpr float kMaxFov = 170.0f * xe::Math::Const::DegToRad;
	m_fov = xe::Math::Clamp(fov, kMinFov, kMaxFov);
}

void Camera::SetAspectRatio(float ratio)
{
	m_aspectRatio = ratio;
}

float xe::Graphics::Camera::GetAspectRatio()
{
	return m_aspectRatio;
}

void Camera::SetSize(float width, float height)
{
	m_width = width;
	m_height = height;
}

void Camera::SetNearPlane(float nearPlane)
{
	m_nearPlane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
	m_farPlane = farPlane;
}

void Camera::Walk(float distance)
{
	m_position += m_direction * distance;
}

void Camera::Strafe(float distance)
{
	const xe::Math::Vector3 right = xe::Math::Normalize(Cross(xe::Math::Vector3::YAxis, m_direction));
	m_position += right * distance;
}

void Camera::Rise(float distance)
{
	m_position += xe::Math::Vector3::YAxis * distance;
}

void Camera::Yaw(float radian)
{
	xe::Math::Matrix4 matRotate = xe::Math::Matrix4::RotationY(radian);
	m_direction = xe::Math::TransformNormal(m_direction, matRotate);
}

void Camera::Pitch(float radian)
{
	const xe::Math::Vector3 right = xe::Math::Normalize(Cross(xe::Math::Vector3::YAxis, m_direction));
	const xe::Math::Matrix4 matRot = xe::Math::Matrix4::RotationAxis(right, radian);
	const xe::Math::Vector3 newLook = xe::Math::TransformNormal(m_direction, matRot);
	SetDirection(newLook);
}

void Camera::Zoom(float amount)
{
	constexpr float minZoom = 170.0f * xe::Math::Const::DegToRad;
	constexpr float maxZoom = 10.0f * xe::Math::Const::DegToRad;
	m_fov = xe::Math::Clamp(m_fov - amount, maxZoom, minZoom);
}

const xe::Math::Vector3& Camera::GetPosition() const
{
	return m_position;
}

const xe::Math::Vector3& Camera::GetDirection() const
{
	return m_direction;
}

xe::Math::Matrix4 Camera::GetViewMatrix() const
{
	const xe::Math::Vector3 l = m_direction;
	const xe::Math::Vector3 r = xe::Math::Normalize(xe::Math::Cross(xe::Math::Vector3::YAxis, l));
	const xe::Math::Vector3 u = xe::Math::Normalize(xe::Math::Cross(l, r));
	const float x = -xe::Math::Dot(r, m_position);
	const float y = -xe::Math::Dot(u, m_position);
	const float z = -xe::Math::Dot(l, m_position);

	return
	{
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		x,   y,   z,   1.0f
	};
}

xe::Math::Matrix4 Camera::GetProjectionMatrix() const
{
	return (m_projectionMode == ProjectionMode::Perspective) ? GetPerspectiveMatrix() : GetOrthographicMatrix();
}

xe::Math::Matrix4 Camera::GetPerspectiveMatrix() const
{
	const float a = (m_aspectRatio == 0.0f) ? GraphicsSystem::Get().GetBackBufferAspectRatio() : m_aspectRatio;
	const float h = 1.0f / tan(m_fov * 0.5f);
	const float w = h / a;
	const float zf = m_farPlane;
	const float zn = m_nearPlane;
	const float q = zf / (zf - zn);

	return {
		w,    0.0f, 0.0f,    0.0f,
		0.0f, h,    0.0f,    0.0f,
		0.0f, 0.0f, q,       1.0f,
		0.0f, 0.0f, -zn * q, 0.0f
	};
}

xe::Math::Matrix4 Camera::GetOrthographicMatrix() const
{
	const float w = (m_width == 0.0f) ? GraphicsSystem::Get().GetBackBufferWidth() : m_width;
	const float h = (m_height == 0.0f) ? GraphicsSystem::Get().GetBackBufferHeight() : m_height;
	const float f = m_farPlane;
	const float n = m_nearPlane;
	return 	{
		2 / w, 0.0f,  0.0f,        0.0f,
		0.0f,  2 / h, 0.0f,        0.0f,
		0.0f,  0.0f,  1 / (f - n), 0.0f,
		0.0f,  0.0f,  n / (n - f), 1.0f
	};
}