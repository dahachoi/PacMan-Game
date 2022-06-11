#include "CRedGhost.h"

using namespace std;

CRedGhost::CRedGhost() {
	InitVariables();
	InitSprite();
}

void CRedGhost::ScatterState()
{
}

void CRedGhost::ChaseState()
{
}

void CRedGhost::InitVariables()
{
	mMovementX = 1.f;
	mMovementY = 0.f;
	mX = 13 * 27 + 13;
	mY = 14 * 27 + 13;
	mName = "Blinky";
}

void CRedGhost::InitSprite()
{
	mTexture.loadFromFile("Game_resources/Ghosts/RedRight.png");
	mGhost.setTexture(mTexture);

	mGhost.setOrigin(mGhost.getGlobalBounds().width / 2, mGhost.getGlobalBounds().height / 2);
	mGhost.setPosition(mX, mY);
}

void CRedGhost::UpdateDirTexture()
{
	switch (mDir) {
	case DIRECTION::LEFT:
		mTexture.loadFromFile("Game_resources/Ghosts/RedLeft.png");
		break;
	case DIRECTION::RIGHT:
		mTexture.loadFromFile("Game_resources/Ghosts/RedRight.png");
		break;
	case DIRECTION::UP:
		mTexture.loadFromFile("Game_resources/Ghosts/RedUP.png");
		break;
	case DIRECTION::DOWN:
		mTexture.loadFromFile("Game_resources/Ghosts/RedDown.png");
		break;
	}
}
