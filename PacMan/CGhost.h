#pragma once

#include <iostream>
#include <set>

#include "SFML/Graphics.hpp"

#include "Direction.h"
#include "mapSketch.h"

enum class	BEHAVIOUR{NONE = 0, SCATTER, CHASE, FRIGHTENED, EATEN};

class CGhost
{
public:
	CGhost() = default;
	virtual void Update();
	virtual void Render(sf::RenderTarget*);
	//Helpers
	void SetPosition(const float&, const float&);
	void StopGhost();
	const sf::Sprite& GetShape() const;
	const sf::Vector2f GetGridCoordinate() const;
	const DIRECTION& GetDir() const;
	void SwitchDirection(const DIRECTION&);
	const void SwitchScatter();
	const void SwitchChase();
	const void SwitchFrightened();
	const void SwitchEaten();
	void SwitchManualBhvr(const BEHAVIOUR&);
	const BEHAVIOUR& GetBehaviour() const;
	const void ReverseDir();

	//Update
	virtual void UpdateTarget(const float&, const float&) = 0;
	void ChooseNextTile();

protected:
	BEHAVIOUR mState = BEHAVIOUR::SCATTER;
	std::string mName;

	//Sprite
	sf::Sprite mGhost;
	sf::Texture mTexture;

	float mX;
	float mY;
	float mMovementSpeed = 1.f;
	float mMovementX;
	float mMovementY;

	short targetI;
	short targetJ;
	
	DIRECTION mDir;

	sf::Clock mFrightenedClock;
	sf::Time mFrightenedTime;

	//Functions
	void FrightenedState();
	void EatenState();
	void UpdateMove();
	bool TileBlocked(const DIRECTION&);
	bool IsInGhostBox();
	float CalculateDistance(const DIRECTION&);
	bool SpecialIntersection();
	bool BlinkFrightenedTextures();
	int mBlinkTimer = 0;

	//Initialization Functions
	virtual void InitVariables() = 0;
	virtual void InitSprite() = 0;

	//Update
	virtual void UpdateDirTexture() = 0;
};

