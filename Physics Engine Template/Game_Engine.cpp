#include "Game_Engine.h"


Game_Engine::Game_Engine() // constructor just calls the init functions to clean up the code a bit and make it easier to read
{
	this->initWindow();
	this->initVariables();
}

Game_Engine::~Game_Engine()
{
	delete this->_window;

	for (int i = 0; i < _objectList.size(); i++)
	{
		delete _objectList[i];
	}
}

void Game_Engine::initWindow() // initializes the _window with the title and size
{
	// sf::_videoMode::getDesktopMode().width * 0.5f, sf::_videoMode::getDesktopMode().height * 0.7f
	this->_videoMode = sf::VideoMode(800, 1000);
	this->_window = new sf::RenderWindow(this->_videoMode, "Template", sf::Style::Close | sf::Style::Titlebar);
	

	this->_window->setFramerateLimit(60);
}

void Game_Engine::initVariables() // basic initialization function
{
	_gravity = 0.f; // higher number = more _gravity
	_drag = 0.99f; // higher number = less _drag
	_engineTools = Engine_Tools();
	_objectList = std::vector<Rigid_Body*>();
	_maps = Maps();
	_isMouseHeld = false;
	_mouseImpulseDampening = 0.3f;
	_mouseLineActive = false;
	_mouseLine = sf::RectangleShape(sf::Vector2f(0, 0));
	_rectForTexHead = sf::RectangleShape(sf::Vector2f(0, 0));
	_currentStrokeCount = 0;
	_totalStrokeCount = 0;


	_player = new Rigid_Body(false, true, 1);
	_player->SetSize(sf::Vector2f(20, 50));
	_player->SetColor(sf::Color::Red);
	_player->SetPosition(sf::Vector2f(400, 700));
	_player->SetRadius(10);
	_player->SetOrigin();

	_maps.SpawnMainMenu();
	_currentState = mainMenu;
	_objectList.push_back(_player);
	_maps.AddToVectorPool(_objectList);

	std::system("dir");
	_textureBody = sf::Texture(); // loads the textures for the mouse line
	_textureBody.loadFromFile("Textures/Arrow_Pointer_Sprite_Body-1.png");
	_textureHead = sf::Texture();
	_textureHead.loadFromFile("Textures/Arrow_Pointer_Sprite_Pointer-1.png");
	_textureMap = sf::Texture();
	_textureMap.loadFromFile("Textures/Checker_Board.png");
	_spriteMap = sf::Sprite(_textureMap);

	_font = sf::Font();
	_font.loadFromFile("Fonts/ARCADECLASSIC.TTF");
	_strokeCountText = sf::Text();
	_strokeCountText.setFillColor(sf::Color::Black);
	_strokeCountText.setPosition(50, 900);
	_strokeCountText.setFont(_font);
	_strokeCountText.setCharacterSize(30);
	_strokeCountText.setString("Strokes	 " + std::to_string(_currentStrokeCount));

}

void Game_Engine::PollEvents()
{
	while (this->_window->pollEvent(this->_event)) // for now this is just for closing the _window. might add more later but i doubt it
	{
		switch(this->_event.type)
		{
			case sf::Event::Closed:
				this->_window->close();
				break;
			case sf::Event::KeyPressed:
				if(this->_event.key.code == sf::Keyboard::Escape)
					this->_window->close();
				break;
			case sf::Event::MouseButtonReleased:
				ApplyForce();
				break;
		}
	}
}

void Game_Engine::PhysicsUpdate()
{
	_player->SetVelocity(_player->GetVelocity() * _drag); // applies _drag to the object
	if ((_player->GetVelocity().x < 0.13 && _player->GetVelocity().x > -0.13) && (_player->GetVelocity().y < 0.13 && _player->GetVelocity().y > -0.13)) // if the velocity is close to 0
	{
		_player->SetVelocity(sf::Vector2f(0, 0)); // set the velocity to 0
	}
	
}

void Game_Engine::CollisionResolve(int indexShapeA, int indexShapeB, sf::Vector2f normal, float depth)
{
	sf::Vector2f relativeVelocity = _objectList[indexShapeB]->GetVelocity() - _objectList[indexShapeA]->GetVelocity(); // calculates the relative velocity


	float e = _engineTools.MinValue(_objectList[indexShapeA]->GetRestitution(), _objectList[indexShapeB]->GetRestitution()); // calculates the restitution

	float j = -(1 + e) *_engineTools.DotProduct(relativeVelocity, normal);
	j /= (1.f / _objectList[indexShapeA]->_mass + (1.f / _objectList[indexShapeB]->_mass)); // calculates the impulse

	sf::Vector2f impulse = j * normal; // calculates the impulse


	//if ((!_objectList[indexShapeA]->GetCollidable() || !_objectList[indexShapeB]->GetCollidable())) // if either object is not collidable
	//{
	//	return;
	//}
	//if (_objectList[indexShapeA]->GetLockedPosition() && _objectList[indexShapeB]->GetLockedPosition()) // if both objects are locked
	//{
	//	return;
	//}
	if (!(_objectList[indexShapeA]->GetLockedPosition() || _objectList[indexShapeB]->GetLockedPosition())) // if neither object is locked
	{
		_objectList[indexShapeA]->SetPosition(_objectList[indexShapeA]->GetPosition() + normal * depth / 2.f); // move each object half the depth
		_objectList[indexShapeB]->SetPosition(_objectList[indexShapeB]->GetPosition() - normal * depth / 2.f);

		_objectList[indexShapeA]->SetVelocity(_objectList[indexShapeA]->GetVelocity() - impulse * _objectList[indexShapeA]->_mass); // applies the impulse to the velocity
		_objectList[indexShapeB]->SetVelocity(_objectList[indexShapeB]->GetVelocity() + impulse * _objectList[indexShapeB]->_mass);
		return; // return to prevent further calculations
	}
	if (_objectList[indexShapeA]->GetLockedPosition()) // if object A is locked
	{
		//j *= _objectList[indexShapeA]->GetRestitution();
		_objectList[indexShapeB]->SetPosition(_objectList[indexShapeB]->GetPosition() - normal * depth); // move object B the full depth
		_objectList[indexShapeB]->SetVelocity(_objectList[indexShapeB]->GetVelocity() + impulse * _objectList[indexShapeB]->_mass);

		return;
	}
	if (_objectList[indexShapeB]->GetLockedPosition()) // if object B is locked
	{
		//j *= _objectList[indexShapeB]->GetRestitution();
		_objectList[indexShapeA]->SetPosition(_objectList[indexShapeA]->GetPosition() + normal * depth); // move object A the full depth
		_objectList[indexShapeA]->SetVelocity(_objectList[indexShapeA]->GetVelocity() - impulse * _objectList[indexShapeA]->_mass);

		return;
	}
}


void Game_Engine::CollisionCheck()
{
	sf::Vector2f normal;
	float depth;

	for (int i = 0; i < _objectList.size(); i++) // loops through the object list and checks for collisions
	{
		for (int k = i + 1; k < _objectList.size(); k++)
		{
			if ((!_objectList[i]->GetCollidable() || !_objectList[k]->GetCollidable())) // if either object is not collidable
			{
				return;
			}
			if (_objectList[i]->GetLockedPosition() && _objectList[k]->GetLockedPosition()) // if both objects are locked
			{
				return;
			}
			if (_objectList[i]->GetShapeType() == 0 && _objectList[k]->GetShapeType() == 0) // if both objects are rectangles
			{
				std::vector<sf::Vector2f> verticesA =		_objectList[i]->GetVertices(_objectList[i]->GetPointCount()); // create an array of vertices for each object
				std::vector<sf::Vector2f> verticesB =		_objectList[k]->GetVertices(_objectList[k]->GetPointCount());
				if (_engineTools.SATPolygonCollision(verticesA, verticesB, normal, depth)) { CollisionResolve(i, k, normal, depth); } // check for collision and resolve it
			}
			else if (_objectList[i]->GetShapeType() == 0 && _objectList[k]->GetShapeType() == 1) // if one object is a rectangle and the other a circle. might be able to make this prettier later
			{
				float circleRadius =						_objectList[k]->GetRadius();
				sf::Vector2f circleCenter =					_objectList[k]->GetPosition();
				sf::Vector2f polygonCenter =					_objectList[i]->GetPosition();
				std::vector<sf::Vector2f>vertices =			_objectList[i]->GetVertices(_objectList[i]->GetPointCount());
				if (_engineTools.SATCircleToPolyCollision(circleCenter, circleRadius, polygonCenter, vertices, normal, depth)) { CollisionResolve(i, k, normal, depth); }
			}
			else if (_objectList[i]->GetShapeType() == 1 && _objectList[k]->GetShapeType() == 0) // if one object is a circle and the other a rectangle
			{
				float circleRadius =						_objectList[i]->GetRadius();
				sf::Vector2f circleCenter =					_objectList[i]->GetPosition();
				sf::Vector2f polygonCenter =					_objectList[k]->GetPosition();
				std::vector<sf::Vector2f> vertices =		_objectList[k]->GetVertices(_objectList[k]->GetPointCount());
				if (_engineTools.SATCircleToPolyCollision(circleCenter, circleRadius, polygonCenter, vertices, normal, depth)) { CollisionResolve(i, k, normal, depth); }
				
			}
			else if (_objectList[i]->GetShapeType() == 1 && _objectList[k]->GetShapeType() == 1) // if both objects are circles
			{
				float circleRadiusA =						_objectList[i]->GetRadius();
				sf::Vector2f circleCenterA =				_objectList[i]->GetPosition();
				sf::Vector2f circleCenterB =				_objectList[k]->GetPosition();
				float circleRadiusB =						_objectList[k]->GetRadius();
				if (_engineTools.CircleCollision(circleCenterA, circleRadiusA, circleCenterB, circleRadiusB, normal, depth)) { CollisionResolve(i, k, normal, depth); }
				
			}
			
		}
	}

}

void Game_Engine::ScoreHandling()
{
	if (_engineTools.Distance(_player->GetPosition(), _maps.GetGoalPosition()) <= _maps.GetGoalRadius())
	{
		_player->SetVelocity(sf::Vector2f(0, 0));
		_player->SetPosition(sf::Vector2f(400, 700));
		_totalStrokeCount += _currentStrokeCount;
		_currentStrokeCount = 0;

		_maps.SpawnNextLevel();
		_strokeCountText.setString("Strokes	 " + std::to_string(_currentStrokeCount));
	}
}


void Game_Engine::Movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // moves the object left
	{
		//_player->SetVelocity(sf::Vector2f(_player->GetVelocity().x - 0.5f, _player->GetVelocity().y));
		_player->AddForce(sf::Vector2f(-0.5f, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // moves the object right
	{
		_player->AddForce(sf::Vector2f(0.5f, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // moves the object up
	{
		_player->AddForce(sf::Vector2f(0, -0.5f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // moves the object down
	{
		_player->AddForce(sf::Vector2f(0, 0.5f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // resets the velocity of the object
	{
		_player->SetVelocity(sf::Vector2f(0, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // random
	{
		_maps.SpawnMap3();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{
		sf::FloatRect _playerBounds = _player->GetCircle().getGlobalBounds(); // assigns a Rect to the _player to ease the process of checking if the mouse is within the bounds of the _player

		if (!(_player->GetVelocity() == sf::Vector2f(0, 0))) // dont let the user click if the character is moving
		{
			return;
		}
		if (_playerBounds.contains(sf::Vector2f(sf::Mouse::getPosition(*_window).x, sf::Mouse::getPosition(*_window).y))) // if the mouse is within the bounds of the _player set mouse as being held down
		{
			_isMouseHeld = true;
			_mouseLineActive = true;
		}
		if (_isMouseHeld) // if the mouse is held get the distance between the mouse and _player to use as the impulse value
		{
			sf::Vector2f normal = _engineTools.Normalize(sf::Vector2f(sf::Mouse::getPosition(*_window)) - _player->GetPosition());
			normal = -normal;

			_mouseDistance = _engineTools.Distance(_player->GetPosition(), sf::Vector2f(sf::Mouse::getPosition(*_window)));
			_mouseLine = sf::RectangleShape({ _mouseDistance*2, 70 });
			_mouseLine.setOrigin(_mouseDistance/4.5, 34);
			_mouseLine.setPosition(_player->GetPosition());
			_mouseLine.setRotation(std::atan2(normal.y, normal.x) * 180 / 3.141);
			_mouseLine.setTexture(&_textureBody);

			_rectForTexHead = sf::RectangleShape({ 70, 70 });
			_rectForTexHead.setOrigin(35, 33);
			_rectForTexHead.setPosition(_player->GetPosition() + normal * (_mouseDistance*2) / 1.53f); // is this the best way to do it? no. do i care? kinda but i aint fixing all that so we're just gonna deal with it
			_rectForTexHead.setRotation(std::atan2(normal.y, normal.x) * 180 / 3.141);
			_rectForTexHead.setTexture(&_textureHead);


		}
	}
	// see the event queue for the mouse button release
	// for some reason button release is only an event so i need to run that throught the poll events function
}

void Game_Engine::ApplyForce()
{
	switch (_isMouseHeld)
	{
		case false: // ensures that no needless calculations are made whenever i let go of the mouse button
			break;
		case true:
			sf::Vector2f normal = _engineTools.Normalize(sf::Vector2f(sf::Mouse::getPosition(*_window)) - _player->GetPosition()); // creates the normal direction to apply the force to
			normal = -normal; // inverts the normal so that dragging the mouse down shoots the player up
			_player->AddForce({ normal * _mouseDistance * _mouseImpulseDampening }); // apply the impulse to the _player

			//// reset all variables ////
			_isMouseHeld = false;
			_mouseLineActive = false;
			_mouseDistance = 0;

			//// handle the stroke counters ////
			_currentStrokeCount++;
			_strokeCountText.setString("Strokes	 " + std::to_string(_currentStrokeCount));
			break;
	}
	
}

void Game_Engine::Update()
{
	switch (_currentState)
	{
		case mainMenu:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // do the simple checks first to reduce computation time
			{
				if (_maps.GetPlayButton()->GetRectangle().getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*_window).x, sf::Mouse::getPosition(*_window).y)))
				{
					_maps.SpawnMap1();
					_currentState = game;
					_maps.deleteMenu();
				}
			}
			break;
		case levelSelect: // work in progress
			break;
		case game: // dont run all of these complex function unless the actual game is running
			PhysicsUpdate();
			CollisionCheck();
			Movement();

			for (int i = 0; i < _objectList.size(); i++)
			{
				_objectList[i]->Update(_gravity);
			}
			ScoreHandling();
			_maps.Update();
			break;
	}
	PollEvents(); // always run PollEvents since it handles things like closing the game
	
}

void Game_Engine::Render()
{
	this->_window->clear(); // clears the frame and sets the color of the _window the rgb value specified
	this->_window->draw(_spriteMap); // draws the background texture



	switch (_currentState)
	{
	case mainMenu:
		_maps.Render(this->_window);
		break;
	case levelSelect:
		break;
	case game:
		for (int i = _objectList.size() - 1; i >= 0; i--) // player is first in render queue so i itterate backwards to make sure its always on top. no way im adding a layer system
		{
			_objectList[i]->Render(this->_window);
		}
		if (_mouseLineActive) // if the mouse line is active render it
		{
			this->_window->draw(_mouseLine);
			this->_window->draw(_rectForTexHead);
		}
		break;
	}

	this->_window->draw(_strokeCountText);
	this->_window->display(); // displayed the frame with the updated information
}


