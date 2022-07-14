#include "C_Box0.h"
namespace C
{
	Box0::Box0(GameObject* gameObject)
		:Component(gameObject){}
		
	void Box0::Start()
	{
		
	}
	
	void Box0::Update()
	{
		if (InputSystem::KeyHold(Key::Up))
			gameObject->transform.position.y += speed * Time::DeltaTime();
		if (InputSystem::KeyHold(Key::Down))
			gameObject->transform.position.y -= speed * Time::DeltaTime();
		if (InputSystem::KeyHold(Key::Right))
			gameObject->transform.position.x += speed * Time::DeltaTime();
		if (InputSystem::KeyHold(Key::Left))
			gameObject->transform.position.x -= speed * Time::DeltaTime();

		if (GetComponent<Collider>()->GetTrigger() != nullptr)
			Debug::LogInfo("Collision");
	}
}
