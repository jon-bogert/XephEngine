#include "Utility.h"
#include "InputSystem.h"

xe::Utility::Utility()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 450), "XephEngine - Debug Utility", sf::Style::Close);
    window->setFramerateLimit(15);

    font.loadFromFile("Assets/Fonts/Retro Gaming.ttf");
    
    runText.setString("[1] Run Application");
    runText.setFont(font);
    runText.setCharacterSize(fontSize);
    runText.setFillColor(textColor);
    runText.setOrigin({ runText.getLocalBounds().width / 2, runText.getLocalBounds().height / 2 });
    runText.setPosition({ 200, 350 });

    createText.setString("[2] Create Script");
    createText.setFont(font);
    createText.setCharacterSize(fontSize);
    createText.setFillColor(textColor);
    createText.setOrigin({ createText.getLocalBounds().width / 2, createText.getLocalBounds().height / 2 });
    createText.setPosition({ 600, 350 });
}

xe::Utility::~Utility()
{
	delete window;
}

int xe::Utility::Runtime()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        Update();
        window->clear(bgColor);
        Draw();
        window->display();
    }
    return menuSel;
}

void xe::Utility::Update()
{
    if (InputSystem::KeyEvent(Key::_1) == Pressed)
    {
        window->close();
        menuSel = 1;
    }
    else if (InputSystem::KeyEvent(Key::_2) == Pressed)
    {
        window->close();
        menuSel = 2;
    }
}

void xe::Utility::Draw()
{
    window->draw(runText);
    window->draw(createText);
}
