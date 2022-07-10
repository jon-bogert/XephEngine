#include "C_OtherTestObj.h"
namespace C
{
	OtherTestObj::OtherTestObj(GameObject* gameObject)
		:Component(gameObject){}
		
	void OtherTestObj::Start()
	{
		//myTestObj = FindObjectOfType<MyTestObj>();
	}
	
	void OtherTestObj::Update()
	{
		if (InputSystem::KeyEvent(Key::Space) == Pressed) Instantiate(new O::MyTestObj());
	}
}
