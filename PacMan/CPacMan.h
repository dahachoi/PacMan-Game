#pragma once

#include <iostream>
#include <math.h>

#include "SFML/Graphics.hpp"

#include "Direction.h"

class CPacMan
{
public:
	CPacMan();

	//Get & Set Functions
	void SetPosition(const float&, const float&);
	const sf::CircleShape& GetShape() const;
	const sf::Vector2f GetGridCoordinate() const;
	const DIRECTION& GetCurrDir() const;
	const DIRECTION& GetQuedDir() const;

	//Functions
	void SwitchDirection();
	const void StopPacMan();
	const bool IsStopped() const;

	//Update & Render
	void Update();
	void Render(sf::RenderTarget*);
private:
	sf::CircleShape mPacMan;

	//Position
	float mX;
	float mY;

	//Movement
	DIRECTION mCurrDir;
	DIRECTION mQuedDir;

	float mMovementSpeed;
	float mMovementX;
	float mMovementY;

	//Initialization Functions
	void InitVariables();
	void InitPacMan();

	//Update
	void UpdateInput();
	void UpdateMove();
	//Render
};

