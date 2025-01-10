#include "Maps.h"


Maps::Maps()
{
	_playButton =			new Rigid_Body(true, false, 0);
	_selectLevelButton =	new Rigid_Body(true, false, 0);

	_playText =				sf::Text();
	_selectLevelText =		sf::Text();
	_congradulationsText =	sf::Text();
	_scoreText =			sf::Text();

	_font = sf::Font();
	_font.loadFromFile("Fonts/ARCADECLASSIC.TTF");

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

void Maps::SpawnMainMenu()
{
    _activeLVL = 0;



    // Set positions and sizes for the buttons
    _playButton->SetPosition({ 400, 300 });
    _playButton->SetSize({ 200, 50 });
    _selectLevelButton->SetPosition({ 400, 400 });
    _selectLevelButton->SetSize({ 200, 50 });

    // Set colors for the buttons
    _playButton->SetColor({ 200, 140, 50, 255 }); // Green for Play
    _selectLevelButton->SetColor({ 200, 140, 50, 255 }); // Blue for Select Level

    // Set rectangle origins
    _playButton->SetRecOrigin();
    _selectLevelButton->SetRecOrigin();

	_playText.setFont(_font);
	_selectLevelText.setFont(_font);
	_playText.setCharacterSize(24);
	_selectLevelText.setCharacterSize(24);
	_playText.setFillColor(sf::Color::Black);
	_selectLevelText.setFillColor(sf::Color::Black);
	_playText.setString("Play");
	_selectLevelText.setString("Select Level");
	_playText.setPosition({ 375, 285 });
	_selectLevelText.setPosition({ 325, 385 });
}

void Maps::SpawnNextLevel(int finalStrokeCount)
{
	CleanUp();
	switch (_activeLVL)
	{
	case 0:
		break;
	case 1:
		SpawnMap2();
		break;
	case 2:
		SpawnMap3();
		break;
	case 3:
		SpawnEndScreen(finalStrokeCount);
		break;
	}
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
	_goal->SetRadius(13);


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


	_recObstacle1->SetPosition({ 400, 400 });
	_recObstacle2->SetPosition({ 400, 400 });

	_recObstacle3->SetPosition({ 400, 200 });
	_recObstacle4->SetPosition({ 400, 200 });

	_recObstacle1->SetSize({ 100, 5 });
	_recObstacle2->SetSize({ 100, 5 });
	_recObstacle3->SetSize({ 100, 5 });
	_recObstacle4->SetSize({ 100, 5 });

	_recObstacle1->SetRotation(90);
	_recObstacle2->SetRotation(0);
	_recObstacle3->SetRotation(90);
	_recObstacle4->SetRotation(0);

	_goal->SetPosition({ 400, 300 });

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

void Maps::SpawnMap3()
{

	_activeLVL = 3;

	_wall1->SetPosition({ 400, 800 });
	_wall2->SetPosition({ 300, 580 });
	_wall3->SetPosition({ 270, 160 });
	_wall4->SetPosition({ 500, 480 });

	_wall5->SetPosition({ 40, 265 });
	_wall6->SetPosition({ 180, 370 });

	_wall1->SetSize({ 240, 40 });
	_wall2->SetSize({ 40, 400 });
	_wall3->SetSize({ 500, 40 });
	_wall4->SetSize({ 40, 600 });
	_wall5->SetSize({ 40, 250 });
	_wall6->SetSize({ 280, 40 });

	_wall1->SetColor({ 200, 140, 50, 255 });
	_wall2->SetColor({ 200, 140, 50, 255 });
	_wall3->SetColor({ 200, 140, 50, 255 });
	_wall4->SetColor({ 200, 140, 50, 255 });
	_wall5->SetColor({ 200, 140, 50, 255 });
	_wall6->SetColor({ 200, 140, 50, 255 });


    _recObstacle1->SetPosition({ 450, 240 });
    _recObstacle2->SetPosition({ 414, 240 });
    _recObstacle3->SetPosition({ 415, 207 });

    _recObstacle1->SetSize({ 70, 5 });
    _recObstacle2->SetSize({ 95, 5 });
    _recObstacle3->SetSize({ 70, 5 });

    _recObstacle1->SetRotation(90);
    _recObstacle2->SetRotation(45);
    _recObstacle3->SetRotation(0);

	_recObstacle1->SetColor(sf::Color::White);
	_recObstacle2->SetColor(sf::Color::White);
	_recObstacle3->SetColor(sf::Color::White);

	_goal->SetPosition({ 150, 260 });

	_wall1->SetRecOrigin();
	_wall2->SetRecOrigin();
	_wall3->SetRecOrigin();
	_wall4->SetRecOrigin();
	_wall5->SetRecOrigin();
	_wall6->SetRecOrigin();
	_recObstacle1->SetRecOrigin();
	_recObstacle2->SetRecOrigin();
	_recObstacle3->SetRecOrigin();
	_goal->SetRecOrigin();
}

void Maps::SpawnEndScreen(int finalScore)
{
	_activeLVL = 4;
	// Set colors for the buttons
	_congradulationsText.setFont(_font);
	_scoreText.setFont(_font);

	_congradulationsText.setCharacterSize(62);
	_scoreText.setCharacterSize(32);

	_congradulationsText.setFillColor(sf::Color::Black);
	_scoreText.setFillColor(sf::Color::Black);

	_congradulationsText.setPosition({ 140, 285 });
	_scoreText.setPosition({ 281, 399 });

	_congradulationsText.setString("Congradulations!");
	_scoreText.setString("S h o t s      T a k e n      " + std::to_string(finalScore));
}

void Maps::CleanUp()
{
    _wall1->SetPosition({ -1000, -1000 });
    _wall2->SetPosition({ -1000, -1000 });
    _wall3->SetPosition({ -1000, -1000 });
    _wall4->SetPosition({ -1000, -1000 });
    _wall5->SetPosition({ -1000, -1000 });
    _wall6->SetPosition({ -1000, -1000 });

    _recObstacle1->SetPosition({ -1000, -1000 });
    _recObstacle2->SetPosition({ -1000, -1000 });
    _recObstacle3->SetPosition({ -1000, -1000 });
    _recObstacle4->SetPosition({ -1000, -1000 });

    _circObstacle1->SetPosition({ -1000, -1000 });
    _circObstacle2->SetPosition({ -1000, -1000 });
    _circObstacle3->SetPosition({ -1000, -1000 });
    _circObstacle4->SetPosition({ -1000, -1000 });

	_goal->SetPosition({ -1000, -1000 });

    // Reset rotation of all objects to 0
    _wall1->SetRotation(0);
    _wall2->SetRotation(0);
    _wall3->SetRotation(0);
    _wall4->SetRotation(0);
    _wall5->SetRotation(0);
    _wall6->SetRotation(0);
    
    _recObstacle1->SetRotation(0);
    _recObstacle2->SetRotation(0);
    _recObstacle3->SetRotation(0);
    _recObstacle4->SetRotation(0);
    
    _circObstacle1->SetRotation(0);
    _circObstacle2->SetRotation(0);
    _circObstacle3->SetRotation(0);
    _circObstacle4->SetRotation(0);
}


void Maps::Update()
{
	switch (_activeLVL)
	{
	case 1:
		break;
	case 2:
		_recObstacle1->SpinRect(20);
		_recObstacle2->SpinRect(20);
		_recObstacle3->SpinRect(-20);
		_recObstacle4->SpinRect(-20);
		break;
	}
}

void Maps::Render(sf::RenderWindow* window)
{
	switch (_activeLVL)
	{
	case 0:
		_playButton->Render(window);
		_selectLevelButton->Render(window);
		window->draw(this->_playText);
		window->draw(this->_selectLevelText);
		break;
	case 4:
		window->draw(this->_congradulationsText);
		window->draw(this->_scoreText);
		break;
	}
}
