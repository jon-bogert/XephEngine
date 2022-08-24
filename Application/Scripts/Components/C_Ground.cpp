#include "C_Ground.h"
namespace C
{
	Ground::Ground(GameObject* gameObject)
		:Component(gameObject){}
		
	void Ground::Start()
	{
		//GetComponent<Collider>()->SetIsTrigger(true);
	}
	
	void Ground::Update()
	{
	}
}
