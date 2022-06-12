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
	InitCoins();
}

void CMap::InitWalls() {
	mWallsTexture.loadFromFile("Game_Resources/Map/PacMan Map.png");

	mWalls.setTexture(mWallsTexture);
	mWalls.setPosition(0, 0);
}

void CMap::InitCoins() {

	for (int i = 4; i < 35; ++i) {
		for (int j = 0; j < 28; ++j) {
			if (mMapSketch[i][j] == 'c') {
				float y = i * 27.f + 13.f;
				float x = j * 27.f + 13.f;
				mCoins[make_pair(i, j)] = new CCoin(x, y);
			}
			else if (mMapSketch[i][j] == 'e') {
				float y = i * 27.f + 13.f;
				float x = j * 27.f + 13.f;
				mCoins[make_pair(i, j)] = new CEnergizer(x, y);
			}
		}
	}
}

bool CMap::UpdateWallCollision(float& x, float& y, const DIRECTION& dir) {
	int i = static_cast<int>(y / 27);
	int j = static_cast<int>(x / 27);

	//cout << "x, y : (" << x << ", " << y << ")" << endl;
	//cout << "current pacman: " << i << ", " << j << endl;
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

	if (mMapSketch[i][j] == '#' || mMapSketch[i][j] == '@') return true;

	return false;
}

int CMap::UpdateCoinCollision(const float& x, const float& y) {
	int i = static_cast<int>(y / 27);
	int j = static_cast<int>(x / 27);

	int gainPoints = 0;

	if (mMapSketch[i][j] == 'c' || mMapSketch[i][j] == 'e') {
		auto it = mCoins.find({ i, j });
		mCoins.erase(it);
		
		if (mMapSketch[i][j] == 'c') gainPoints = 10;
		else gainPoints = 50;

		mMapSketch[i][j] = ' ';
	}
	return gainPoints;
}

void CMap::Render(sf::RenderTarget* target) {
	target->draw(mWalls);
	
	for (auto it = mCoins.begin(); it != mCoins.end(); ++it) {
		it->second->Render(target);
	}
}