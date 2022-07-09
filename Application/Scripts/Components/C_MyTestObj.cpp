#include "C_MyTestObj.h"
namespace C
{
	MyTestObj::MyTestObj(GameObject* gameObject)
		:Component(gameObject){}
		
	void MyTestObj::Start()
	{

	}
	
	void MyTestObj::Update()
	{
		//PrintTest();
	}
	void MyTestObj::PrintTest()
	{
		std::cout << "Print Test!" << std::endl;
	}
}
