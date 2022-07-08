#include "C_TestComp.h"

namespace C
{
	TestComp::TestComp(GameObject* gameObject)
		:Component(gameObject) {}

	void TestComp::Start()
	{
		text = GetComponent<C::Text>();
		//text->SetString("Boring...");
		//SaveData saveData("Test");
		//saveData.AddString("TestMessage", "This is a test message. I hope it works!");
		//saveData.AddString("NameFirst", "Jonathan");
		//saveData.AddString("NameLast", "Bogert");
		//saveData.AddString("Username", "Xepherin");
		//saveData.AddInt("Age", 23);
		//saveData.AddVector2("Position", Vector2(100, -98));
		//saveData.AddBool("OfAge", true);

		//SaveData saveData = FileSystem::Load("Test");

		//saveData.ChangeName("Test2");

		//FileSystem::Save(saveData);
	}

	void TestComp::Update()
	{
		//std::string str = text->GetString();
		//InputSystem::Typing(str);
		//text->SetString(str);

	}
}
