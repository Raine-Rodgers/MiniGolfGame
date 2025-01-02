#include "Map1.h"


Map1::Map1()
{
	_wall1 = new Rigid_Body(true, true, 0);
	_wall2 = new Rigid_Body(true, true, 0);
	_wall3 = new Rigid_Body(true, true, 0);
	_wall4 = new Rigid_Body(true, true, 0);

	_wall1->SetPosition({ 140, 10 });
	_wall2->SetPosition({ 100, 10 });
	_wall3->SetPosition({ 100, 800 });
	_wall4->SetPosition({ 650, 10 });

	_wall1->SetSize({ 510, 40 });
	_wall2->SetSize({ 40, 800 });
	_wall3->SetSize({ 550, 40 });
	_wall4->SetSize({ 40, 830 });

	_wall1->SetColor({ 0, 0, 0, 255 });	  // black
	_wall2->SetColor({ 255, 0, 0, 255 }); // red
	_wall3->SetColor({ 0, 255, 0, 255 }); // green
	_wall4->SetColor({ 0, 0, 255, 255 }); // blue

	_tempObjectTransferPool = std::vector<Rigid_Body*>(); // theres for sure a better way to do this but i can think of it so for now im just gonna allocate this to the free store and delete it after use to not waste memory i guess
	_tempObjectTransferPool.push_back(_wall1);
	_tempObjectTransferPool.push_back(_wall2);
	_tempObjectTransferPool.push_back(_wall3);
	_tempObjectTransferPool.push_back(_wall4);
}

Map1::~Map1()
{
}


void Map1::addToVectorPool(std::vector<Rigid_Body*>& tempVec)
{
	tempVec.push_back(_wall1);
	tempVec.push_back(_wall2);
	tempVec.push_back(_wall3);
	tempVec.push_back(_wall4);
}


void Map1::update()
{
}

