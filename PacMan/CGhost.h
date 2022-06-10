#pragma once

#include "SFML/Graphics.hpp"

enum class	BEHAVIOUR{SCATTER = 0, CHASE, FRIGHTENED, EATEN};

class CGhost
{
public:
	virtual void Update() = 0;
	virtual void Render(sf::RenderTarget*) = 0;
private:

	BEHAVIOUR mState = BEHAVIOUR::SCATTER;
	std::string mName;

	//Sprite
	sf::Sprite mGhost;
	sf::Texture mTexture;

	float mX;
	float mY;
	float mMovementSpeed = 1.f;

	virtual void ScatterState() = 0;
	virtual void ChaseState() = 0;
	void FrightenedState();
	void EatenState();
};

