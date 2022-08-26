#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class Collider : public Component
	{
	protected:
		bool isTrigger = false;
		bool isStatic = true;
		bool hasGravity = false;

		float width;
		float height;

		Vector2 velocity = { 0.f, 0.f };
		Vector2 moveBuffer = { 0.f, 0.f };
	
	public:
		Collider(float width, float height, GameObject* gameObject);
		
		void Start() override;
		void Update() override;
		void LateUpdate() override;
		void Move(Vector2 directionSpeed);
		void PhysicsApply();
		void OnDestroy() override;

		bool GetIsTrigger() const;
		bool GetHasGravity() const;
		bool GetIsStatic() const;
		Vector2 GetDimensions() const;
		float GetLeft();
		float GetRight();
		float GetTop();
		float GetBottom();

		void SetIsTrigger(const bool _isTrigger);
		void SetHasGravity(const bool _hasGravity);
		void SetIsStatic(const bool _isStatic);

		void ApplyAcceleration(const Vector2& accel);
		void ApplyCurrentVelocity();
		void SetVelocity(const Vector2& newVel);
		void ResetVelocity();
		Vector2 GetVelocity() const;

		Vector2 GetPosition() const;
		void SetPosition(const Vector2 newPosition);

		Vector2 GetMoveBuffer() const;
		void SetMoveBuffer(const Vector2 newMoveBuffer);
		Rectangle MoveBufferRect();
		Rectangle MoveBufferRectX(); //Rectangle where only X direction Move Buffer is applied
		Rectangle MoveBufferRectY(); //Rectangle where only Y direction Move Buffer is applied

	private:
		bool CheckStatic();
	};
}

