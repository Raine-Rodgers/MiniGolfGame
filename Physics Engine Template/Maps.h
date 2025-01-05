#pragma once

#include <iostream>
#include "Rigid_Body.h"

class Maps
{
private:
	// main walls
	Rigid_Body* _wall1;
	Rigid_Body* _wall2;
	Rigid_Body* _wall3;
	Rigid_Body* _wall4;
	Rigid_Body* _wall5;
	Rigid_Body* _wall6;

	// map obstacles
	Rigid_Body* _recObstacle1;
	Rigid_Body* _recObstacle2;
	Rigid_Body* _recObstacle3;
	Rigid_Body* _recObstacle4;

	Rigid_Body* _circObstacle1;
	Rigid_Body* _circObstacle2;
	Rigid_Body* _circObstacle3;
	Rigid_Body* _circObstacle4;

	Rigid_Body* _goal;

	std::vector<Rigid_Body*> _tempObjectTransferPool;
	int _activeLVL;

public:
	void			addToVectorPool(std::vector<Rigid_Body*>& tempVec);
	int 			getVectorPoolSize() { return _tempObjectTransferPool.size(); }

	void			spawnMap1();
	void			spawnMap2();

	Maps();
	~Maps();

	void Update();
};

