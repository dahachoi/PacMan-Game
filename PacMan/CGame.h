#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "CMap.h"
#include "CPacMan.h"
#include "CRedGhost.h"

class CGame
{
public:
	CGame();
	~CGame();

	const bool Running() const;
	void Update();
	void Render();
private:
	sf::RenderWindow* mWindow;
	sf::VideoMode mVideoMode;
	sf::Event mEv;
	bool mEndGame;

	//28 blocks across // 840
	//36 blocks down //1080 pixels down
	//27x27 pixels
	const unsigned WIDTH = 756;
	const unsigned HEIGHT = 972;

	//Game Objects
	CMap iMap;
	CPacMan iPacMan;
	CRedGhost iRedGhost;

	short unsigned mScore;
	const short unsigned mMaxScore;
	short unsigned mGainPoints;

	//Time
	sf::Clock mClock;
	sf::Time mTime;
	int mChaseWave = 1;

	//Functions
	void PollEvents();

	//Initialization Functions
	void InitWindow();
	void InitVariables();

	//Update
	void UpdatePacMan();
	void UpdateGhosts();
	void UpdateGhostTarget(const float&, const float&);
	void UpdatePacManCollision();
	void UpdateGhostCollision();
	void UpdateCollision();
	void UpdateGhostBehaviour();

	//Render
	void RenderMap();
	void RenderGhosts();
};

