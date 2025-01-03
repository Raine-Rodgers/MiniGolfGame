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
	_map1 = Map1();
	_isMouseHeld = false;
	_mouseImpulseDampening = 0.3f;

	_goal = new Rigid_Body(false, true, 1);
	//_goal->SetSize(sf::Vector2f(100, 50));
	_goal->SetColor(sf::Color::Red);
	_goal->SetPosition(sf::Vector2f(400, 400));
	_goal->SetRadius(20);
	_goal->SetOrigin();

	_player = new Rigid_Body(false, true, 1);
	_player->SetSize(sf::Vector2f(20, 50));
	_player->SetColor(sf::Color::Green);
	_player->SetPosition(sf::Vector2f(400, 500));
	_player->SetRadius(20);
	_player->SetOrigin();


	_objectList.push_back(_goal);
	_objectList.push_back(_player);
	_map1.addToVectorPool(_objectList);
	std::cout << _objectList.size() << std::endl;
	//_objectList.push_back(orgin);



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

	
	std::cout << _player->GetVelocity().x << " " << _player->GetVelocity().y << "\n";

	if (!(_objectList[indexShapeA]->GetCollidable() || _objectList[indexShapeB]->GetCollidable())) // if either object is not collidable
	{
		return;
	}
	if (_objectList[indexShapeA]->GetLockedPosition() && _objectList[indexShapeB]->GetLockedPosition()) // if both objects are locked
	{
		return;
	}
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

		//std::cout << normal.x << " " << normal.y << std::endl;
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
			if (_objectList[i]->GetShapeType() == 0 && _objectList[k]->GetShapeType() == 0) // if both objects are rectangles
			{
				std::vector<sf::Vector2f> verticesA =		_objectList[i]->GetVertices(_objectList[i]->GetPointCount()); // create an array of vertices for each object
				std::vector<sf::Vector2f> verticesB =		_objectList[k]->GetVertices(_objectList[k]->GetPointCount());
				if (_engineTools.SATPolygonCollision(verticesA, verticesB, normal, depth)) { CollisionResolve(i, k, normal, depth); } // check for collision and resolve it
				//std::cout << "rect collision" << std::endl;
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
		}
		if (_isMouseHeld) // if the mouse is held get the distance between the mouse and _player to use as the impulse value
		{
			_mouseDistance = _engineTools.Distance(_player->GetPosition(), sf::Vector2f(sf::Mouse::getPosition(*_window)));
			std::cout << _mouseDistance << "\n";
		}
	}
	// see the event queue for the mouse button release
	// for some reason button release is only an event so i need to run that throught the poll events function
}

void Game_Engine::ApplyForce()
{
	//sf::Vector2f(sf::Mouse::getPosition(*_window)) - _player->GetPosition()
	sf::Vector2f normal = _engineTools.Normalize(sf::Vector2f(sf::Mouse::getPosition(*_window)) - _player->GetPosition());
	normal = -normal;
	_player->AddForce({ normal * _mouseDistance * _mouseImpulseDampening }); // apply the impulse to the _player
	_isMouseHeld = false;
	_mouseDistance = 0;
}

void Game_Engine::Update()
{
	PhysicsUpdate();
	CollisionCheck();

	for (int i = 0; i < _objectList.size(); i++)
	{
		_objectList[i]->Update(_gravity);
	}
	PollEvents();
	Movement();
}

void Game_Engine::Render()
{
	this->_window->clear(sf::Color(46, 74, 94)); // clears the frame and sets the color of the _window the rgb value specified

	for (int i = 0; i < _objectList.size(); i++) // iterates through the object list and renders each object
	{
		_objectList[i]->Render(this->_window);
	}

	this->_window->display(); // displayed the frame with the updated information
}


