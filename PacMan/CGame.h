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
#include "CPinkGhost.h"

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
	std::vector<CGhost*> mGhostContainer;
	CRedGhost iRedGhost;

	short unsigned mScore;
	const short unsigned mMaxScore;
	short unsigned mGainPoints;

	//Time
	sf::Clock mClock;
	sf::Time mTime;
	sf::Clock mFrightenedClock;
	sf::Time mFrightenedTime = sf::milliseconds(0);
	sf::Time mDeltaTime;
	BEHAVIOUR mLastBhvr = BEHAVIOUR::NONE;
	int mChaseWave = 1;
	void SwitchAllGhostBhvr(const BEHAVIOUR&);

	//Functions
	void PollEvents();

	//Initialization Functions
	void InitWindow();
	void InitVariables();
	void InitGhosts();

	//Update
	void UpdatePacMan();
	void UpdateGhosts();
	void UpdateGhostTarget(const float&, const float&);
	void UpdatePacManCollision();
	void UpdateGhostCollision(CGhost*);
	void UpdateCollision(CGhost *);
	void UpdateGhostBehaviour(CGhost*);

	//Render
	void RenderMap();
	void RenderGhosts();
};

