#include "C_Box1.h"
namespace C
{
	Box1::Box1(GameObject* gameObject)
		:Component(gameObject){}
		
	void Box1::Start()
	{
		Debug::Log("BAM!");
	}
	
	void Box1::Update()
	{
		
	}
}
