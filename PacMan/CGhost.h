#pragma once

#include "SFML/Graphics.hpp"

enum class	BEHAVIOUR{SCATTER = 0, CHASE, FRIGHTENED, EATEN};

class CGhost
{
public:
	void Update();
	void Render(sf::RenderTarget*);
private:

};

