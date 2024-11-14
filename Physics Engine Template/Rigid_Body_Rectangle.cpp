#include "Rigid_Body_Rectangle.h"


Rigid_Body_Rectangle::Rigid_Body_Rectangle() : Rigid_Body()
{
	this->size = sf::Vector2f(100, 30);
	this->position = sf::Vector2f(500, 500);
	this->rectangle.setSize(this->size);
	this->rectangle.setPosition(this->position);
	this->rectangle.setFillColor(sf::Color::Red);
	this->rectangle.setRotation(45);
}

Rigid_Body_Rectangle::Rigid_Body_Rectangle(sf::Vector2f acceleration, sf::Vector2f velocity, float mass, float friction, sf::Vector2f size, sf::Vector2f position, bool lockedPosition, float terminalVelocity)
: Rigid_Body(acceleration, velocity, mass, friction, lockedPosition, terminalVelocity)
{
	this->size = size;
	this->position = position;
	

	this->rectangle.setSize(this->size);
}

Rigid_Body_Rectangle::~Rigid_Body_Rectangle()
{
}

void Rigid_Body_Rectangle::Update()
{
}

void Rigid_Body_Rectangle::Render(sf::RenderWindow* window)
{
	window->draw(this->rectangle);
}
