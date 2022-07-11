#include "C_OtherTestObj.h"
namespace C
{
	OtherTestObj::OtherTestObj(GameObject* gameObject)
		:Component(gameObject){}
		
	void OtherTestObj::Start()
	{
		//myTestObj = FindObjectOfType<MyTestObj>();
		Debug::LogWarn("Printing number %f", 1.993f);
		Debug::LogErr("This is a very bad %s!", std::string("Error").c_str());
		Debug::LogInfo("Just some info...");
	}
	
	void OtherTestObj::Update()
	{
		//if (InputSystem::KeyEvent(Key::Space) == Pressed) Destroy(FindObjectOfType<MyTestObj>()->GetGameObject());
	}
}
