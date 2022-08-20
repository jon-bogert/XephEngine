#include "C_Collider.h"
namespace C
{
	Collider::Collider(float width, float height, GameObject* gameObject)
		: Component(gameObject)
		, width(width)
		, height(height)
	{
	}
		
	void Collider::Start()
	{
		
	}
	
	void Collider::Update()
	{
		
	}

	void Collider::LateUpdate()
	{

	}

	void Collider::Move(Vector2 directionSpeed)
	{
		if (CheckStatic()) return;

		moveBuffer.x += directionSpeed.x;
		moveBuffer.y += directionSpeed.y;
	}


	bool Collider::GetIsTrigger() const
	{
		return isTrigger;
	}
	bool Collider::GetHasGravity() const
	{
		return hasGravity;
	}
	Vector2 Collider::GetDimensions() const
	{
		return Vector2(width, height);
	}
	void Collider::SetIsTrigger(const bool _isTrigger)
	{
		isTrigger = _isTrigger;
	}
	float Collider::GetTop()
	{
		return gameObject->transform.position.y - (height * 0.5f);
	}
	float Collider::GetLeft()
	{
		return gameObject->transform.position.x - (width * 0.5f);
	}
	void Collider::SetHasGravity(const bool _hasGravity)
	{
		hasGravity = _hasGravity;
	}
	float Collider::GetRight()
	{
		return gameObject->transform.position.x + (width * 0.5f);
	}
	Vector2 Collider::GetPosition() const
	{
		return gameObject->transform.position;
	}
	float Collider::GetBottom()
	{
		return gameObject->transform.position.y + (height * 0.5f);
	}
	void Collider::SetPosition(const Vector2 newPosition)
	{
		gameObject->transform.position = newPosition;
	}
	bool Collider::GetIsStatic() const
	{
		return (isStatic);
	}
	void Collider::SetVelocity(const Vector2& newVel)
	{
		if (CheckStatic()) return;
		velocity = newVel;
	}
	void Collider::ResetVelocity()
	{
		velocity = { 0.f, 0.f };
	}
	Vector2 Collider::GetVelocity() const
	{
		return velocity;
	}
	void Collider::SetIsStatic(const bool _isStatic)
	{
		isStatic = _isStatic;
	}
	void Collider::ApplyAcceleration(const Vector2& accel)
	{
		if (CheckStatic()) return;
		velocity.x += accel.x * Time::DeltaTime();
		velocity.y += accel.y * Time::DeltaTime();
	}
	bool Collider::CheckStatic()
	{
		if (isStatic)
			Debug::LogWarn("Must call .SetIsStatic(false) on collider to move");
		return isStatic;
	}
	Vector2 Collider::GetMoveBuffer() const
	{
		return moveBuffer;
	}
}
