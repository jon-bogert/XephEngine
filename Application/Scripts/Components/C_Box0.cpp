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

		if (InputSystem::KeyEvent(Key::Space) == Pressed)
			GetComponent<PhysicsBox>()->AddImpulse({ 0, 10 });

		if(InputSystem::KeyEvent(Key::Left) == Pressed)
			GetComponent<PhysicsBox>()->AddImpulse({ -5, 2 });
		if(InputSystem::KeyEvent(Key::Right) == Pressed)
			GetComponent<PhysicsBox>()->AddImpulse({ 5, 2 });
		
		count++;
		if (count % 3 == 0)
			Debug::Log("Message %i", count);
		else if (count % 3 == 1)
			Debug::LogWarn("Message %i", count);
		else
			Debug::LogErr("Message %i", count);
		/*if (InputSystem::KeyHold(Key::Up))
		{
			gameObject->transform.position.x += Math::ForwardVector(gameObject->transform.rotation.GetRotation()).x * speed * Time::DeltaTime();
			gameObject->transform.position.y += Math::ForwardVector(gameObject->transform.rotation.GetRotation()).y * speed * Time::DeltaTime();
		}

		if (InputSystem::KeyHold(Key::Right)) gameObject->transform.rotation.Add(90 * Time::DeltaTime());
		if (InputSystem::KeyHold(Key::Left)) gameObject->transform.rotation.Add(-90 * Time::DeltaTime());*/
		

		/*if (GetComponent<Collider>()->GetTrigger() != nullptr)
			Debug::Log("Collision");*/
	}
}
