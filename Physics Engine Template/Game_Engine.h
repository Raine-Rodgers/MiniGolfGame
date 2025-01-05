#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Rigid_Body.h"
#include "Engine_Tools.h"
#include "Maps.h"

class Game_Engine
{
private:
	void						initWindow();
	void						initVariables();

	sf::VideoMode				_videoMode;
	sf::RenderWindow*			_window;
	sf::Event					_event;
	Engine_Tools				_engineTools;
	float						_gravity;
	float						_drag;
	float						_mouseDistance;
	float						_mouseImpulseDampening;
	std::vector<Rigid_Body*>	_objectList;
	Maps						_maps;
	bool						_isMouseHeld;


	// test variables
	Rigid_Body*	_goal;
	Rigid_Body*	_player;

	int count = 0;


public:
	const bool					running() const { return this->_window->isOpen(); } // returns if the window is open or not
	void						PollEvents();
	void						ApplyForce();
	void						Movement();
	void						PhysicsUpdate();
	void						CollisionCheck();
	void						CollisionResolve(int indexShapeA, int indexShapeB, sf::Vector2f normal, float depth);
	void						Update();
	void						Render();

	Game_Engine();
	~Game_Engine();
};

