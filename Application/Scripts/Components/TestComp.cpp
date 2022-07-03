#include "TestComp.h"

TestComp::TestComp(GameObject* gameObject)
	:Component(gameObject){}

void TestComp::Start()
{
	std::cout << "Test start has been called" << std::endl;
}

void TestComp::Update()
{

}
