#include "Window.h"
#include "Libraries.h"

float deltaTime = 0.f;

xe::Window::Window()
{
	//TODO Run Project Settings Script
	UpdateResolutionScale();
	window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), title, sf::Style::Close);
	clock = new sf::Clock();
}

xe::Window::~Window()
{
	delete clock;
	delete window;
}

void xe::Window::Draw()
{
	window->clear(sf::Color::Black); // TODO from Camera

	for (Component* comp : drawables)
		DrawCalc(comp);

	//sf::Texture t;
	//t.loadFromFile("Assets/Textures/test.png");
	//sf::Sprite s;
	//s.setTexture(t);
	//window->draw(s);

	window->display();
}

void xe::Window::DrawCalc(Component* comp)
{
	
	// Safeguard
	if (comp->Draw() == nullptr)
	{
		std::cout << "[INFO] No Drawable found on Component type: " << typeid(*comp).name() << std::endl;
		return;
	}

	window->draw(*comp->Draw());
}

bool xe::Window::IsOpen()
{
	return window->isOpen();
}

void xe::Window::Close()
{
	window->close();
}

sf::RenderWindow* xe::Window::SF_Window()
{
	return window;
}

void xe::Window::UpdateResolutionScale()
{
	resolutionScale = resolution.y / (float)referenceResolution.y;
}

void xe::Window::UpdateFrameClock()
{
	deltaTime = clock->getElapsedTime().asSeconds();
	clock->restart();
}

void xe::Window::ResetFrameClock()
{
	clock->restart();
}

std::vector <xe::Component* > & xe::Window::GetDrawables()
{
	return drawables;
}

float xe::Window::GetPixelsPerUnit() const
{
	return pixelsPerUnit;
}

float xe::Window::GetResolutionScale() const
{
	return resolutionScale;
}

float xe::Window::WidthInUnits() const
{
	return referenceResolution.x / pixelsPerUnit;
}

float xe::Window::HeightInUnits() const
{
	return referenceResolution.y / pixelsPerUnit;
}

float xe::Time::DeltaTime()
{
	return deltaTime;
}

float xe::Time::FPS()
{
	if (deltaTime <= 0.f)
		return 0.f;

	return 1.f/deltaTime;
}

void xe::Time::UpdateDelta()
{
	Engine::GetWindow()->UpdateFrameClock();
}

void xe::Time::ResetDelta()
{
	Engine::GetWindow()->ResetFrameClock();
}

void xe::Draw::SpriteCalc(sf::Sprite* drawable, Component* comp) // TODO - Implement Camera Scale and Rotation
{
	Transform goTransform = comp->GetGameObject()->transform;
	Transform camera = Engine::GetActiveScene()->GetCamera();
	drawable->setPosition
	( //goTransform.postion.x, goTransform.postion.y
		(goTransform.postion.x
			- (camera.postion.x /*+ (camera.scale.x / 2)*/))
		* Engine::GetWindow()->GetPixelsPerUnit()
		* Engine::GetWindow()->GetResolutionScale(),

		(goTransform.postion.y
			- (camera.postion.y /*+ (camera.scale.y / 2)*/))
		* Engine::GetWindow()->GetPixelsPerUnit()
		* Engine::GetWindow()->GetResolutionScale()
	);

	drawable->setScale(goTransform.scale.x * camera.scale.x * Engine::GetWindow()->GetResolutionScale(),
		goTransform.scale.y * camera.scale.y * Engine::GetWindow()->GetResolutionScale());
}
