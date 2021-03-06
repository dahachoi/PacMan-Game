#include "CPinkGhost.h"

using namespace std;

CPinkGhost::CPinkGhost()
{
	InitVariables();
	InitSprite();
}


void CPinkGhost::InitVariables(){
	mMovementX = -1.f;
	mMovementY = 0.f;
	mDir = DIRECTION::LEFT;
	mX = 12 * 27;
	mY = 14 * 27 + 13;
	mName = "Pinky";

	targetI = 0;
	targetJ = 2;

	mInGhostBox = false;
}

void CPinkGhost::InitSprite()
{
	mTexture.loadFromFile("Game_resources/Ghosts/PinkLeft.png");
	mGhost.setTexture(mTexture);

	mGhost.setOrigin(mGhost.getGlobalBounds().width / 2, mGhost.getGlobalBounds().height / 2);
	mGhost.setPosition(mX, mY);
}

void CPinkGhost::UpdateTarget(const float& pacManX, const float& pacManY, const DIRECTION& pacManDir, const float& blinkyX, const float& blinkyY) {
	if (IsInGhostBox() && mState != BEHAVIOUR::EATEN) {
		targetI = 15;
		targetJ = 14;
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

void CPinkGhost::CalculateTarget(const float& pacManX, const float& pacManY, const DIRECTION& pacManDir, const float& blinkyX, const float& blinkyY) {
	//Pinky targets 4 spaces in front of pacMan, unless pacman is facing up then it targets 4 up and left.
	targetI = static_cast<int>(pacManY / 27);
	targetJ = static_cast<int>(pacManX / 27);

	//cout << "pacMan : " << targetI << ", " << targetJ << endl;
	switch (pacManDir) {
	case DIRECTION::UP:
		targetI -= 4;
		targetJ -= 4;
		break;
	case DIRECTION::DOWN:
		targetI += 4;
		break;
	case DIRECTION::LEFT:
		targetJ -= 4;
		break;
	case DIRECTION::RIGHT:
		targetJ += 4;
		break;
	}

	//cout << "pink is targeting : " << targetI << ", " << targetJ << endl;
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
		//cout << "mFrightenedTime : " << mFrightenedTime.asSeconds() << endl;
		if (mFrightenedTime.asSeconds() >= 5) {
			if (BlinkFrightenedTextures()) mTexture.loadFromFile("Game_resources/Ghosts/FrightenedGhost.png");
			else mTexture.loadFromFile("Game_resources/Ghosts/FrightenedCoolDown.png");
		}
		else mTexture.loadFromFile("Game_resources/Ghosts/FrightenedGhost.png");
	}
}
