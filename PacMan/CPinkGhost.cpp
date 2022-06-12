#include "CPinkGhost.h"

using namespace std;

CPinkGhost::CPinkGhost()
{
	InitVariables();
	InitSprite();
}


void CPinkGhost::InitVariables(){
	mMovementX = 1.f;
	mMovementY = 0.f;
	mDir = DIRECTION::LEFT;
	mX = 14 * 27;
	mY = 14 * 27 + 13;
	mName = "Pinky";

	targetI = 0;
	targetJ = 2;
}

void CPinkGhost::InitSprite()
{
	mTexture.loadFromFile("Game_resources/Ghosts/PinkLeft.png");
	mGhost.setTexture(mTexture);

	mGhost.setOrigin(mGhost.getGlobalBounds().width / 2, mGhost.getGlobalBounds().height / 2);
	mGhost.setPosition(mX, mY);
}

void CPinkGhost::UpdateTarget(const float& x, const float& y)
{
	if (IsInGhostBox() && mState != BEHAVIOUR::EATEN) {
		targetI = 15;
		targetJ = 14.5;
		mMovementSpeed = .5f;
		return;
	}

	switch (mState) {
	case BEHAVIOUR::SCATTER:
		targetI = 0;
		targetJ = 2;
		mMovementSpeed = 1.f;
		break;
	case BEHAVIOUR::CHASE:
		targetI = y / 27;
		targetJ = x / 27;
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

void CPinkGhost::UpdateDirTexture()
{
	if (mState == BEHAVIOUR::CHASE || mState == BEHAVIOUR::SCATTER) {
		switch (mDir) {
		case DIRECTION::LEFT:
			mTexture.loadFromFile("Game_resources/Ghosts/PinkLeft.png");
			break;
		case DIRECTION::RIGHT:
			mTexture.loadFromFile("Game_resources/Ghosts/PinkRight.png");
			break;
		case DIRECTION::UP:
			mTexture.loadFromFile("Game_resources/Ghosts/PinkUP.png");
			break;
		case DIRECTION::DOWN:
			mTexture.loadFromFile("Game_resources/Ghosts/PinkDown.png");
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
		cout << "mFrightenedTime : " << mFrightenedTime.asSeconds() << endl;
		if (mFrightenedTime.asSeconds() >= 5) {
			if (BlinkFrightenedTextures()) mTexture.loadFromFile("Game_resources/Ghosts/FrightenedGhost.png");
			else mTexture.loadFromFile("Game_resources/Ghosts/FrightenedCoolDown.png");
		}
		else mTexture.loadFromFile("Game_resources/Ghosts/FrightenedGhost.png");
	}
}
