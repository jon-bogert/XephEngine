#include "C_MyTestObj.h"
namespace C
{
	MyTestObj::MyTestObj(GameObject* gameObject)
		:Component(gameObject){}
		
	void MyTestObj::Start()
	{
		ss = GetComponent<SpriteSheet>();
		ss->SetupAnimated({"red", "green", "blue"}, {3, 2, 5});
	}
	
	void MyTestObj::Update()
	{
		//PrintTest();
		gameObject->transform.rotation.Add(45 * Time::DeltaTime());
	}
	void MyTestObj::PrintTest()
	{
		
	}
}
