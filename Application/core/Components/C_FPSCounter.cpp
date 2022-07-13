#include "C_FPSCounter.h"
namespace C
{
	C::FPSCounter::FPSCounter(GameObject* gameObject)
		:Component(gameObject) {}

	void C::FPSCounter::Start()
	{
		text = GetComponent<Text>();
		if (text == nullptr) std::cout << "[ERROR] FPSCounter_Comp could not find 'Text' Component" << std::endl;
	}

	void C::FPSCounter::Update()
	{
		text->SetString(std::to_string((int)Time::FPS()));
		gameObject->transform.position = {text->GetOriginOffset().x, Engine::GetWindow()->HeightInUnits() - text->GetOriginOffset().y};
	}
}
