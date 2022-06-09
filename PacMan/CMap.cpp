#include "CMap.h"

using namespace std;

CMap::CMap() {
	InitVariables();
	InitMap();
}

void CMap::InitVariables() {

}

void CMap::InitMap() {
	InitWalls();
}

void CMap::InitWalls() {
	mWallsTexture.loadFromFile("Game_Resources/Map/PacMan Map.png");

	mWalls.setTexture(mWallsTexture);
	mWalls.setPosition(0, 0);
}

bool CMap::UpdateCollision(float& x, float& y, const DIRECTION& dir) {
	int i = static_cast<int>(y / 27);
	int j = static_cast<int>(x / 27);

	cout << "x, y : (" << x << ", " << y << ")" << endl;
	cout << "current pacman: " << i << ", " << j << endl;
	switch (dir) {
	case DIRECTION::RIGHT:
		j++;
		break;
	case DIRECTION::DOWN:
		i++;
		break;
	case DIRECTION::LEFT:
		j--;
		break;
	case DIRECTION::UP:
		i--;
		break;
	}

	if (mMapSketch[i][j] == '#') return true;

	return false;
}

void CMap::Render(sf::RenderTarget* target) {
	target->draw(mWalls);
}