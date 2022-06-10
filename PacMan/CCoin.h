#pragma once

#include "SFML/Graphics.hpp"

class CCoin
{
public:
	CCoin() = default;
	CCoin(const float&, const float&);

	void Render(sf::RenderTarget*);
protected:
	sf::CircleShape mCoin;
	
	float mX;
	float mY;

	virtual void InitCoin();
};

