#include "CRedGhost.h"

using namespace std;

CRedGhost::CRedGhost() {
	InitVariables();
	InitSprite();
}

void CRedGhost::InitVariables()
{
	mMovementX = 1.f;
	mMovementY = 0.f;
	mDir = DIRECTION::RIGHT;
	mX = 16 * 27;
	mY = 14 * 27 + 13;
	mName = "Blinky";

	targetI = 0;
	targetJ = 16;

	mInGhostBox = false;
}


void CRedGhost::InitSprite()
{
	mTexture.loadFromFile("Game_resources/Ghosts/RedRight.png");
	mGhost.setTexture(mTexture);

	mGhost.setOrigin(mGhost.getGlobalBounds().width / 2, mGhost.getGlobalBounds().height / 2);
	mGhost.setPosition(mX, mY);
}


void CRedGhost::UpdateTarget(const float& pacManX, const float& pacManY, const DIRECTION& pacManDir, const float& blinkyX, const float& blinkyY) {
	if (IsInGhostBox() && mState != BEHAVIOUR::EATEN) {
		targetI = 15;
		targetJ = 14;
		mMovementSpeed = .5f;
		return;
	}

	switch (mState) {
	case BEHAVIOUR::SCATTER:
		targetI = 0;
		targetJ = 26;
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

void CRedGhost::CalculateTarget(const float& pacManX, const float& pacManY, const DIRECTION& pacManDir, const float& blinkyX, const float& blinkyY) {
	//Blinkys target is just pacmans location.
	targetI = static_cast<int>(pacManY/ 27);
	targetJ = static_cast<int>(pacManX / 27);
}

void CRedGhost::UpdateDirTexture()
{
	if (mState == BEHAVIOUR::CHASE || mState == BEHAVIOUR::SCATTER) {
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
