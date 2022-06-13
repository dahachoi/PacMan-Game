#include "CYellowGhost.h"

using namespace std;

CYellowGhost::CYellowGhost()
{
	InitVariables();
	InitSprite();
}

void CYellowGhost::InitVariables()
{
	mMovementX = -1.f;
	mMovementY = 0.f;
	mDir = DIRECTION::LEFT;
	mX = 10 * 27;
	mY = 14 * 27 + 13;
	mName = "Clyde";

	targetI = 35;
	targetJ = 0;

	mInGhostBox = false;
}

void CYellowGhost::InitSprite()
{
	mTexture.loadFromFile("Game_resources/Ghosts/YellowRight.png");
	mGhost.setTexture(mTexture);

	mGhost.setOrigin(mGhost.getGlobalBounds().width / 2, mGhost.getGlobalBounds().height / 2);
	mGhost.setPosition(mX, mY);
}

void CYellowGhost::UpdateTarget(const float& pacManX, const float& pacManY, const DIRECTION& pacManDir, const float& blinkyX, const float& blinkyY)
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
		targetJ = 0;
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

void CYellowGhost::CalculateTarget(const float& pacManX, const float& pacManY, const DIRECTION& pacManDir, const float& blinkyX, const float& blinkyY){
	//Clyde just targets the Pacman, until he is within a distance of 8 where he puts his target as scatter.

	int pacManI = static_cast<int>(pacManY / 27);
	int pacManJ = static_cast<int>(pacManX / 27);
	int ghostI = static_cast<int>(mY / 27);
	int ghostJ = static_cast<int>(mX / 27);
	
	int y = abs(pacManI - ghostI);
	int x = abs(pacManJ - ghostJ);

	double distance = sqrt(pow(y, 2) + pow(x, 2));
	/*cout << "distance : " << distance << endl;*/

	targetI = pacManI;
	targetJ = pacManJ;

	if (distance <= 8) {
		targetI = 35;
		targetJ = 0;
	}

}


void CYellowGhost::UpdateDirTexture(){
	if (mState == BEHAVIOUR::CHASE || mState == BEHAVIOUR::SCATTER) {
		switch (mDir) {
		case DIRECTION::LEFT:
			mTexture.loadFromFile("Game_resources/Ghosts/YellowLeft.png");
			break;
		case DIRECTION::RIGHT:
			mTexture.loadFromFile("Game_resources/Ghosts/YellowRight.png");
			break;
		case DIRECTION::UP:
			mTexture.loadFromFile("Game_resources/Ghosts/YellowUP.png");
			break;
		case DIRECTION::DOWN:
			mTexture.loadFromFile("Game_resources/Ghosts/YellowDown.png");
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
