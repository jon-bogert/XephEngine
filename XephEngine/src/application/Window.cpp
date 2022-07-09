#include "Window.h"
#include "../Libraries.h"
#include "../EngineUtils.h"

float deltaTime = 0.f;

xe::Window::Window()
{
	UpdateResolutionScale();
	//RefreshWindow();
	UpdateSettings(FileSystem::LoadProjSettings());
	frameTimer = new Timer;
}

xe::Window::~Window()
{
	delete frameTimer;
	delete window;
}

void xe::Window::UpdateSettings(SaveData settings)
{
	resolution = { (int)settings.GetVector2("Resolution").x, (int)settings.GetVector2("Resolution").y };
	referenceResolution = { (int)settings.GetVector2("ReferenceResolution").x, (int)settings.GetVector2("ReferenceResolution").y };
	UpdateResolutionScale();
	pixelsPerUnit = settings.GetFloat("PixelsPerUnit");
	title = settings.GetString("AppTitle");
	hasFrameLimit = settings.GetBool("HasFrameLimit");
	frameLimit = settings.GetInt("FrameLimit");
	backgroundColor = settings.GetColor("BackgroundColor");

	std::string windowModeStr = settings.GetString("WindowMode");
	if (windowModeStr == "Fullscreen") windowMode = WindowMode::Fullscreen;
	else if (windowModeStr == "Borderless") windowMode = WindowMode::Borderless;
	else windowMode = WindowMode::Windowed;

	RefreshWindow();
}

void xe::Window::RefreshWindow()
{
	delete window;
	window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), title, sf::Style::Close);
	if (hasFrameLimit) window->setFramerateLimit(frameLimit);
}

void xe::Window::Draw()
{
	window->clear(Engine::SF_COLOR(backgroundColor));

	for (Component* comp : drawables)
		DrawCalc(comp);

	window->display();
}

void xe::Window::DrawCalc(Component* comp)
{
	if (comp->GetGameObject()->GetIsActive() && comp->GetIsEnabled())
	{
		// Safeguard
		if (comp->Draw() == nullptr)
		{
			std::cout << "[INFO] No Drawable found on Component type: " << typeid(*comp).name() << std::endl;
			return;
		}

		window->draw(*comp->Draw());
	}
}

bool xe::Window::IsOpen()
{
	return window->isOpen();
}

void xe::Window::Close()
{
	window->close();
}

sf::RenderWindow* xe::Window::UnWrap()
{
	return window;
}

void xe::Window::UpdateResolutionScale()
{
	resolutionScale = resolution.y / (float)referenceResolution.y;
}

void xe::Window::UpdateFrameTimer()
{
	deltaTime = frameTimer->GetElapsed();
	frameTimer->Reset();
}

void xe::Window::ResetFrameTimer()
{
	frameTimer->Reset();
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
	Engine::GetWindow()->UpdateFrameTimer();
}

void xe::Time::ResetDelta()
{
	Engine::GetWindow()->ResetFrameTimer();
}

void xe::Draw::SpriteCalc(sf::Sprite* drawable, Component* comp) // TODO - Implement Camera Scale and Rotation
{
	Transform goTransform = comp->GetGameObject()->transform;
	Transform camera = Engine::GetActiveScene()->GetCamera();
	drawable->setPosition
	( //goTransform.postion.x, goTransform.postion.y
		(goTransform.position.x
			- (camera.position.x /*+ (camera.scale.x / 2)*/))
		* Engine::GetWindow()->GetPixelsPerUnit()
		* Engine::GetWindow()->GetResolutionScale(),

		(goTransform.position.y
			- (camera.position.y /*+ (camera.scale.y / 2)*/))
		* Engine::GetWindow()->GetPixelsPerUnit()
		* Engine::GetWindow()->GetResolutionScale()
	);

	drawable->setScale(goTransform.scale.x * camera.scale.x * Engine::GetWindow()->GetResolutionScale(),
		goTransform.scale.y * camera.scale.y * Engine::GetWindow()->GetResolutionScale());
}

void xe::Draw::TextCalc(sf::Text* drawable, Component* comp)
{
	Transform goTransform = comp->GetGameObject()->transform;
	Transform camera = Engine::GetActiveScene()->GetCamera();
	drawable->setPosition
	( //goTransform.postion.x, goTransform.postion.y
		(goTransform.position.x
			- (camera.position.x /*+ (camera.scale.x / 2)*/))
		* Engine::GetWindow()->GetPixelsPerUnit()
		* Engine::GetWindow()->GetResolutionScale(),

		(goTransform.position.y
			- (camera.position.y /*+ (camera.scale.y / 2)*/))
		* Engine::GetWindow()->GetPixelsPerUnit()
		* Engine::GetWindow()->GetResolutionScale()
	);

	drawable->setScale(goTransform.scale.x * camera.scale.x * Engine::GetWindow()->GetResolutionScale(),
		goTransform.scale.y * camera.scale.y * Engine::GetWindow()->GetResolutionScale());
}
