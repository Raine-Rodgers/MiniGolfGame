#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Game_Engine
{
private:
	void initWindow();
	void initVariables();

	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event event;

	float gravity;
	float drag;
	

public:
	Game_Engine();
	~Game_Engine();

	const bool running() const { return this->window->isOpen(); }
	void CollisionDetection();
	void PollEvents();
	void Update();
	void Render();
};

