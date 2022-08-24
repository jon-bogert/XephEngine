#include "C_Box0.h"
namespace C
{
	Box0::Box0(GameObject* gameObject)
		:Component(gameObject){}
		
	void Box0::Start()
	{
		FindObjectOfType<PhysicsCore>()->SetUseGravity(true);

		collider = GetComponent<Collider>();

		//collider->SetHasGravity(true);
		collider->SetIsStatic(false);

	}
	
	void Box0::Update()
	{
		if (InputSystem::KeyHold(Key::D))
			collider->Move({ 10 * Time::DeltaTime(), 0.f });
		if (InputSystem::KeyHold(Key::A))
			collider->Move({ -10 * Time::DeltaTime(), 0.f });
		if (InputSystem::KeyHold(Key::S))
			collider->Move({ 0.f, -10 * Time::DeltaTime() });
		if (InputSystem::KeyHold(Key::W))
			collider->Move({ 0.f,  10 * Time::DeltaTime()});

	}
	void Box0::OnCollision(GameObject* other)
	{
		if (other->GetComponent<Ground>() != nullptr)
		{
			Debug::Log("Collision with Ground!");
		}
	}
}
