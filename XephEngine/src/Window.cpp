#include "Window.h"
#include "Libraries.h"

xe::Window::Window()
{
	//TODO Run Project Settings Script
	
	window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), title, sf::Style::Close);
}

xe::Window::~Window()
{
	delete window;
}

void xe::Window::Draw()
{
	window->clear(sf::Color::Black); // TODO from Camera
	window->display();
}

bool xe::Window::IsOpen()
{
	return window->isOpen();
}

void xe::Window::Close()
{
	window->close();
}
