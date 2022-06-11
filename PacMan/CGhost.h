#pragma once

#include <iostream>
#include <set>

#include "SFML/Graphics.hpp"

#include "Direction.h"
#include "mapSketch.h"

enum class	BEHAVIOUR{SCATTER = 0, CHASE, FRIGHTENED, EATEN};

class CGhost
{
public:
	CGhost() = default;
	virtual void Update();
	virtual void Render(sf::RenderTarget*);

	//Helpers
	void SetPosition(const float&, const float&);
	const sf::Sprite& GetShape() const;
	const sf::Vector2f GetGridCoordinate() const;
	const DIRECTION& GetDir() const;
	void SwitchDirection(const DIRECTION&);

	//Update
	void UpdateTarget(const float&, const float&);
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
	float targetX;
	float targetY;
	DIRECTION mDir = DIRECTION::RIGHT;

	//Functions
	virtual void ScatterState() = 0;
	virtual void ChaseState() = 0;
	void FrightenedState();
	void EatenState();
	void UpdateMove();
	bool TileBlocked(const DIRECTION&);

	//Initialization Functions
	virtual void InitVariables() = 0;
	virtual void InitSprite() = 0;

	//Update
	virtual void UpdateDirTexture() = 0;
};

