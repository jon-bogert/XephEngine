#include "Pch.h"
#include "Camera.h"

#include "GraphicsSystem.h"

using namespace xe;
using namespace xe::Graphics;

void Camera::SetMode(ProjectionMode mode)
{
	_projectionMode = mode;
}

void Camera::SetPosition(const xe::Math::Vector3& position)
{
	_position = position;
}

void Camera::SetDirection(const xe::Math::Vector3& direction)
{
	// Prevent setting direction straight up or down
	auto dir = xe::Math::Normalize(direction);
	if (xe::Math::Abs(xe::Math::Dot(dir, xe::Math::Vector3::YAxis)) < 0.995f)
		_direction = dir;
}

void Camera::SetLookAt(const xe::Math::Vector3& target)
{
	SetDirection(target - _position);
}

void Camera::SetFov(float fov)
{
	constexpr float kMinFov = 10.0f * xe::Math::Const::DegToRad;
	constexpr float kMaxFov = 170.0f * xe::Math::Const::DegToRad;
	_fov = xe::Math::Clamp(fov, kMinFov, kMaxFov);
}

void Camera::SetAspectRatio(float ratio)
{
	_aspectRatio = ratio;
}

void Camera::SetSize(float width, float height)
{
	_width = width;
	_height = height;
}

void Camera::SetNearPlane(float nearPlane)
{
	_nearPlane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
	_farPlane = farPlane;
}

void Camera::Walk(float distance)
{
	_position += _direction * distance;
}

void Camera::Strafe(float distance)
{
	const xe::Math::Vector3 right = xe::Math::Normalize(Cross(xe::Math::Vector3::YAxis, _direction));
	_position += right * distance;
}

void Camera::Rise(float distance)
{
	_position += xe::Math::Vector3::YAxis * distance;
}

void Camera::Yaw(float radian)
{
	xe::Math::Matrix4 matRotate = xe::Math::Matrix4::RotationY(radian);
	_direction = xe::Math::TransformNormal(_direction, matRotate);
}

void Camera::Pitch(float radian)
{
	const xe::Math::Vector3 right = xe::Math::Normalize(Cross(xe::Math::Vector3::YAxis, _direction));
	const xe::Math::Matrix4 matRot = xe::Math::Matrix4::RotationAxis(right, radian);
	const xe::Math::Vector3 newLook = xe::Math::TransformNormal(_direction, matRot);
	SetDirection(newLook);
}

void Camera::Zoom(float amount)
{
	constexpr float minZoom = 170.0f * xe::Math::Const::DegToRad;
	constexpr float maxZoom = 10.0f * xe::Math::Const::DegToRad;
	_fov = xe::Math::Clamp(_fov - amount, maxZoom, minZoom);
}

const xe::Math::Vector3& Camera::GetPosition() const
{
	return _position;
}

const xe::Math::Vector3& Camera::GetDirection() const
{
	return _direction;
}

xe::Math::Matrix4 Camera::GetViewMatrix() const
{
	const xe::Math::Vector3 l = _direction;
	const xe::Math::Vector3 r = xe::Math::Normalize(xe::Math::Cross(xe::Math::Vector3::YAxis, l));
	const xe::Math::Vector3 u = xe::Math::Normalize(xe::Math::Cross(l, r));
	const float x = -xe::Math::Dot(r, _position);
	const float y = -xe::Math::Dot(u, _position);
	const float z = -xe::Math::Dot(l, _position);

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
	return (_projectionMode == ProjectionMode::Perspective) ? GetPerspectiveMatrix() : GetOrthographicMatrix();
}

xe::Math::Matrix4 Camera::GetPerspectiveMatrix() const
{
	const float a = (_aspectRatio == 0.0f) ? GraphicsSystem::Get().GetBackBufferAspectRatio() : _aspectRatio;
	const float h = 1.0f / tan(_fov * 0.5f);
	const float w = h / a;
	const float zf = _farPlane;
	const float zn = _nearPlane;
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
	const float w = (_width == 0.0f) ? GraphicsSystem::Get().GetBackBufferWidth() : _width;
	const float h = (_height == 0.0f) ? GraphicsSystem::Get().GetBackBufferHeight() : _height;
	const float f = _farPlane;
	const float n = _nearPlane;
	return 	{
		2 / w, 0.0f,  0.0f,        0.0f,
		0.0f,  2 / h, 0.0f,        0.0f,
		0.0f,  0.0f,  1 / (f - n), 0.0f,
		0.0f,  0.0f,  n / (n - f), 1.0f
	};
}