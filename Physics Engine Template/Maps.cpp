#include "Maps.h"


Maps::Maps()
{
	_wall1 = new Rigid_Body(true, true, 0);
	_wall2 = new Rigid_Body(true, true, 0);
	_wall3 = new Rigid_Body(true, true, 0);
	_wall4 = new Rigid_Body(true, true, 0);
	_wall5 = new Rigid_Body(true, true, 0);
	_wall6 = new Rigid_Body(true, true, 0);

	_recObstacle1 = new Rigid_Body(true, true, 0);
	_recObstacle2 = new Rigid_Body(true, true, 0);
	_recObstacle3 = new Rigid_Body(true, true, 0);
	_recObstacle4 = new Rigid_Body(true, true, 0);

	_circObstacle1 = new Rigid_Body(true, true, 1);
	_circObstacle2 = new Rigid_Body(true, true, 1);
	_circObstacle3 = new Rigid_Body(true, true, 1);
	_circObstacle4 = new Rigid_Body(true, true, 1);

	_goal = new Rigid_Body(true, false, 1);

	_activeLVL = 0;
}

Maps::~Maps()
{
}


void Maps::AddToVectorPool(std::vector<Rigid_Body*>& tempVec)
{
	tempVec.push_back(_wall1);
	tempVec.push_back(_wall2);
	tempVec.push_back(_wall3);
	tempVec.push_back(_wall4);
	tempVec.push_back(_wall5);
	tempVec.push_back(_wall6);
	tempVec.push_back(_recObstacle1);
	tempVec.push_back(_recObstacle2);
	tempVec.push_back(_recObstacle3);
	tempVec.push_back(_recObstacle4);
	tempVec.push_back(_circObstacle1);
	tempVec.push_back(_circObstacle2);
	tempVec.push_back(_circObstacle3);
	tempVec.push_back(_circObstacle4);
		
	tempVec.push_back(_goal);
}

void Maps::SpawnMap1()
{
	_activeLVL = 1;

	_wall1->SetPosition({ 400, 50 });
	_wall2->SetPosition({ 125, 425 });
	_wall3->SetPosition({ 380, 840 });
	_wall4->SetPosition({ 675, 445 });

	_wall1->SetSize({ 510, 40 });
	_wall2->SetSize({ 40, 790 });
	_wall3->SetSize({ 550, 40 });
	_wall4->SetSize({ 40, 830 });

    _wall1->SetColor({ 200, 140, 50, 255 }); // wall1 color
    _wall2->SetColor({ 200, 140, 50, 255 }); // wall2 color
    _wall3->SetColor({ 200, 140, 50, 255 }); // wall3 color
    _wall4->SetColor({ 200, 140, 50, 255 }); // wall4 color

	_goal->SetPosition({ 400, 300 });
	_goal->SetRadius(15);


	_wall1->SetRecOrigin();
	_wall2->SetRecOrigin();
	_wall3->SetRecOrigin();
	_wall4->SetRecOrigin();
	_goal->SetOrigin();
	
}

void Maps::SpawnMap2()
{
	_activeLVL = 2;

	_wall1->SetPosition({ 400, 800 });
	_wall2->SetPosition({ 200, 580 });
	_wall3->SetPosition({ 400, 120 });
	_wall4->SetPosition({ 600, 580 });
	_wall5->SetPosition({ 128, 260 });
	_wall6->SetPosition({ 672, 260 }); 

	_wall1->SetSize({ 440, 40 });
	_wall2->SetSize({ 40, 400 });
	_wall3->SetSize({ 730, 40 });
	_wall4->SetSize({ 40, 400 });
	_wall5->SetSize({ 300, 40 });
	_wall6->SetSize({ 300, 40 });

    _wall1->SetColor({ 200, 140, 50, 255 });
    _wall2->SetColor({ 200, 140, 50, 255 });
    _wall3->SetColor({ 200, 140, 50, 255 });
    _wall4->SetColor({ 200, 140, 50, 255 });
    _wall5->SetColor({ 200, 140, 50, 255 });
    _wall6->SetColor({ 200, 140, 50, 255 });

	_wall5->SetRotation(60);
	_wall6->SetRotation(-60);


	_recObstacle1->SetPosition({ 325, 350 });
	_recObstacle2->SetPosition({ 325, 350 });

	_recObstacle3->SetPosition({ 475, 350 });
	_recObstacle4->SetPosition({ 475, 350 });

	_recObstacle1->SetSize({ 100, 5 });
	_recObstacle2->SetSize({ 100, 5 });
	_recObstacle3->SetSize({ 100, 5 });
	_recObstacle4->SetSize({ 100, 5 });

	_recObstacle1->SetRotation(90);
	_recObstacle2->SetRotation(0);
	_recObstacle3->SetRotation(90);
	_recObstacle4->SetRotation(0);

	_wall1->SetRecOrigin();
	_wall2->SetRecOrigin();
	_wall3->SetRecOrigin();
	_wall4->SetRecOrigin();
	_wall5->SetRecOrigin();
	_wall6->SetRecOrigin();
	_recObstacle1->SetRecOrigin();
	_recObstacle2->SetRecOrigin();
	_recObstacle3->SetRecOrigin();
	_recObstacle4->SetRecOrigin();
	_goal->SetRecOrigin();
}


void Maps::Update()
{
	switch (_activeLVL)
	{
	case 1:
		break;
	case 2:
		_recObstacle1->SpinRect(2);
		_recObstacle2->SpinRect(2);
		_recObstacle3->SpinRect(-2);
		_recObstacle4->SpinRect(-2);
		break;
	}
}
