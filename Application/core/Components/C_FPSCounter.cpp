#include "C_FPSCounter.h"

C_FPSCounter::C_FPSCounter(GameObject* gameObject)
	:Component(gameObject){}
	
void C_FPSCounter::Start()
{
	text = GetComponent<Text>();
	if (text == nullptr) std::cout << "[ERROR] FPSCounter_Comp could not find 'Text' Component" << std::endl;
}

void C_FPSCounter::Update()
{
	text->SetString(std::to_string((int)Time::FPS()));
}
