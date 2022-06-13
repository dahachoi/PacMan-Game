#include "CCyanGhost.h"

using namespace std;

CCyanGhost::CCyanGhost()
{
	InitVariables();
	InitSprite();
}


void CCyanGhost::InitVariables() {
	mMovementX = 1.f;
	mMovementY = 0.f;
	mDir = DIRECTION::RIGHT;
	mX = 18 * 27;
	mY = 14 * 27 + 13;
	mName = "Inky";

	targetI = 0;
	targetJ = 16;
	
	mInGhostBox = true;
}

void CCyanGhost::InitSprite(){
	mTexture.loadFromFile("Game_resources/Ghosts/CyanRight.png");
	mGhost.setTexture(mTexture);

	mGhost.setOrigin(mGhost.getGlobalBounds().width / 2, mGhost.getGlobalBounds().height / 2);
	mGhost.setPosition(mX, mY);
}

void CCyanGhost::UpdateTarget(const float& pacManX, const float& pacManY, const DIRECTION& pacManDir, const float& blinkyX, const float& blinkyY)
{
	if (IsInGhostBox() && mState != BEHAVIOUR::EATEN) {
		targetI = 15;
		targetJ = 14;
		mMovementSpeed = .5f;
		return;
	}

	switch (mState) {
	case BEHAVIOUR::SCATTER:
		targetI = 35;
		targetJ = 27;
		mMovementSpeed = 1.f;
		break;
	case BEHAVIOUR::CHASE:
		CalculateTarget(pacManX, pacManY, pacManDir, blinkyX, blinkyY);
		mMovementSpeed = 1.f;
		break;
	case BEHAVIOUR::EATEN:
		targetI = 17;
		targetJ = 13;
		mMovementSpeed = 3.f;
		break;
	case BEHAVIOUR::FRIGHTENED:
		targetI = rand() % 36;
		targetJ = rand() % 28;
		mMovementSpeed = 0.5;
	}
}

void CCyanGhost::CalculateTarget(const float& pacManX, const float& pacManY, const DIRECTION& pacManDir, const float& blinkyX, const float& blinkyY) {
	//Inky draws a vector between pacMan and blinky, then times it by two.
	int pacManI = static_cast<int>(pacManY / 27);
	int pacManJ = static_cast<int>(pacManX / 27);
	int blinkyI = static_cast<int>(blinkyY / 27);
	int blinkyJ = static_cast<int>(blinkyX / 27);

	switch (pacManDir) {
	case DIRECTION::UP:
		targetI -= 2;
		targetJ -= 2;
		break;
	case DIRECTION::DOWN:
		targetI += 2;
		break;
	case DIRECTION::LEFT:
		targetJ -= 2;
		break;
	case DIRECTION::RIGHT:
		targetJ += 2;
		break;
	}

	int slopeI = pacManI - blinkyI;
	int slopeJ = pacManJ - blinkyJ;

	targetI = pacManI + slopeI;
	targetJ = pacManJ + slopeJ;
	
	//cout << "CYAN GHOST TARGETI, TARGET J : " << targetI << ", " << targetJ << endl;
}

void CCyanGhost::UpdateDirTexture() {
	if (mState == BEHAVIOUR::CHASE || mState == BEHAVIOUR::SCATTER) {
		switch (mDir) {
		case DIRECTION::LEFT:
			mTexture.loadFromFile("Game_resources/Ghosts/CyanLeft.png");
			break;
		case DIRECTION::RIGHT:
			mTexture.loadFromFile("Game_resources/Ghosts/CyanRight.png");
			break;
		case DIRECTION::UP:
			mTexture.loadFromFile("Game_resources/Ghosts/CyanUP.png");
			break;
		case DIRECTION::DOWN:
			mTexture.loadFromFile("Game_resources/Ghosts/CyanDown.png");
			break;
		}
	}
	else if (mState == BEHAVIOUR::EATEN) {
		switch (mDir) {
		case DIRECTION::LEFT:
			mTexture.loadFromFile("Game_resources/Ghosts/EyesLeft.png");
			break;
		case DIRECTION::RIGHT:
			mTexture.loadFromFile("Game_resources/Ghosts/EyesRight.png");
			break;
		case DIRECTION::UP:
			mTexture.loadFromFile("Game_resources/Ghosts/EyesUP.png");
			break;
		case DIRECTION::DOWN:
			mTexture.loadFromFile("Game_resources/Ghosts/EyesDown.png");
			break;
		}
	}
	else {
		mFrightenedTime = mFrightenedClock.getElapsedTime();
		if (mFrightenedTime.asSeconds() >= 5) {
			if (BlinkFrightenedTextures()) mTexture.loadFromFile("Game_resources/Ghosts/FrightenedGhost.png");
			else mTexture.loadFromFile("Game_resources/Ghosts/FrightenedCoolDown.png");
		}
		else mTexture.loadFromFile("Game_resources/Ghosts/FrightenedGhost.png");
	}
}


