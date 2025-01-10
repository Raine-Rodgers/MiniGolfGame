#pragma once

#include <iostream>
#include "Rigid_Body.h"

class Maps
{
private:

	Rigid_Body*					_playButton;
	Rigid_Body*					_selectLevelButton;
	// main walls
	Rigid_Body*					_wall1;
	Rigid_Body*					_wall2;
	Rigid_Body*					_wall3;
	Rigid_Body*					_wall4;
	Rigid_Body*					_wall5;
	Rigid_Body*					_wall6;

	// map obstacles
	Rigid_Body*					_recObstacle1;
	Rigid_Body*					_recObstacle2;
	Rigid_Body*					_recObstacle3;
	Rigid_Body*					_recObstacle4;

	Rigid_Body*					_circObstacle1;
	Rigid_Body*					_circObstacle2;
	Rigid_Body*					_circObstacle3;
	Rigid_Body*					_circObstacle4;

	Rigid_Body*					_goal;

	std::vector<Rigid_Body*>	_tempObjectTransferPool;
	int							_activeLVL;

	sf::Text* _playText;
	sf::Text* _selectLevelText;
	sf::Font  _font;

public:

	void						AddToVectorPool(std::vector<Rigid_Body*>& tempVec);
	int 						GetVectorPoolSize()		{ return _tempObjectTransferPool.size(); }
	int							GetActiveLVL()			{ return _activeLVL; }
	Rigid_Body*					GetPlayButton()			{ return _playButton; }
	Rigid_Body*					GetSelectLevelButton()	{ return _selectLevelButton; }

	sf::Vector2f				GetGoalPosition()		{ return _goal->GetPosition(); }
	float						GetGoalRadius()			{ return _goal->GetRadius(); }
	void						SpawnMainMenu();
	void						SpawnNextLevel();
	void						SpawnMap1();
	void						SpawnMap2();
	void						SpawnMap3();
	void						CleanUp();

	Maps();
	~Maps();
	void deleteMenu();

	void Update();
	void Render(sf::RenderWindow* window);
};

