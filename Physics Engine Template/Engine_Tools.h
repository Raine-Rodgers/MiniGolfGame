#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Engine_Tools
{
private:
	void				ProjectVerticesToAxis(std::vector<sf::Vector2f> vertices, sf::Vector2f axis, float& min, float& max); // projects an array of vertices to an axis and find if theres an overlap
	void				ProjectCircleToAxis(sf::Vector2f circleCenter, float circleRadius, sf::Vector2f axis, float& min, float& max); // projects a circle to an axis and find if theres an overlap
	int					FindClosesPointToCircle(sf::Vector2f circleCenter, std::vector<sf::Vector2f> vertices); // finds the closest point on a polygon to a circle

public:
	sf::Clock			_clock;
	sf::Time			_deltaTime;			// Delta time
	float				_dtMultiplier = 30.0f; // Delta time multiplier
	float				_depthBuffer = 0.1f; // Buffer for depth of collision

	bool				SATPolygonCollision(std::vector<sf::Vector2f> verticesA, std::vector<sf::Vector2f> verticesB, sf::Vector2f& normal, float& depth); // Uses separating axis theorem to check if two polygons are colliding
	bool				SATCircleToPolyCollision(sf::Vector2f circleCenter, float circleRadius, sf::Vector2f polygonCenter, std::vector<sf::Vector2f> vertices, sf::Vector2f& normal, float& depth); // Uses separating axis theorem to check if a circle and a polygon are colliding
	bool				CircleCollision(sf::Vector2f circleCenterA, float circleRadiusA, sf::Vector2f circleCenterB, float circleRadiusB, sf::Vector2f& normal, float& depth); // Checks if two circles are colliding

	float				MinValue(float a, float b);
	float				MaxValue(float a, float b);
	float				DotProduct(sf::Vector2f a, sf::Vector2f b);
	float				Length(sf::Vector2f a);
	float				Distance(sf::Vector2f a, sf::Vector2f b);
	float				DetlaTime() { return _deltaTime.asSeconds() * _dtMultiplier; }
	sf::Vector2f		Normalize(sf::Vector2f a);
	sf::Vector2f		ArithmaticMean(std::vector<sf::Vector2f> vertices);

	Engine_Tools();
	~Engine_Tools();
};

