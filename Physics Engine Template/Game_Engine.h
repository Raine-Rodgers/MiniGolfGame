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
	enum gameState
	{
		mainMenu,
		levelSelect,
		game,
	};

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

	Rigid_Body*					_player;

	sf::Texture					_textureBody;
	sf::Texture					_textureHead;
	sf::Texture					_textureMap;
	sf::Sprite					_spriteMap;

	sf::RectangleShape			_rectForTexHead;
	sf::RectangleShape			_mouseLine;
	bool						_mouseLineActive;

	int							_currentStrokeCount;
	int							_totalStrokeCount;

	gameState					_currentState;

	sf::Text					_strokeCountText;
	sf::Font					_font;



public:
	const bool					running() const { return this->_window->isOpen(); } // returns if the window is open or not
	void						PollEvents();
	void						ApplyForce();
	void						Movement();
	void						PhysicsUpdate();
	void						CollisionCheck();
	void						CollisionResolve(int indexShapeA, int indexShapeB, sf::Vector2f normal, float depth);
	void						ScoreHandling();
	void						Update();
	void						Render();

	Game_Engine();
	~Game_Engine();
};

