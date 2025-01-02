#pragma once

#include <iostream>
#include "Rigid_Body.h"

class Map1
{
private:
	Rigid_Body* _wall1;
	Rigid_Body* _wall2;
	Rigid_Body* _wall3;
	Rigid_Body* _wall4;

	std::vector<Rigid_Body*> _tempObjectTransferPool;

public:
	void			addToVectorPool(std::vector<Rigid_Body*>& tempVec);
	int 			getVectorPoolSize() { return _tempObjectTransferPool.size(); }

	Map1();
	~Map1();

	void update();
};

