#include "CGhost.h"

using namespace std;

void CGhost::SetPosition(const float& x, const float& y) {
	mX = x;
	mY = y;

	mGhost.setPosition(mX, mY);
}

void CGhost::StopGhost() {
	mMovementX = 0.f;
	mMovementY = 0.f;
}

const sf::Sprite& CGhost::GetShape() const {
	return mGhost;
}

const sf::Vector2f CGhost::GetGridCoordinate() const {
	float x = mGhost.getPosition().x - 13;
	float y = mGhost.getPosition().y - 13;

	return sf::Vector2f(x, y);
}

const DIRECTION& CGhost::GetDir() const {
	return mDir;
}

const void CGhost::SwitchScatter() {
	mState = BEHAVIOUR::SCATTER;
	UpdateDirTexture();
}
const void CGhost::SwitchChase(){
	mState = BEHAVIOUR::CHASE;
	UpdateDirTexture();
}
const void CGhost::SwitchFrightened() {
	mState = BEHAVIOUR::FRIGHTENED;
	mFrightenedClock.restart();
	UpdateDirTexture();
}
const void CGhost::SwitchEaten() {
	mState = BEHAVIOUR::EATEN;
	UpdateDirTexture();
}

void CGhost::SwitchManualBhvr(const BEHAVIOUR& bhvr) {
	mState = bhvr;
	UpdateDirTexture();
}

const BEHAVIOUR& CGhost::GetBehaviour() const{
	return mState;
}

bool CGhost::IsInGhostBox() {
	return mGhost.getPosition().x >= 11 * 27 + 13 && mGhost.getPosition().x <= 16 * 27 + 13 && mGhost.getPosition().y >= 16 * 27 + 13 && mGhost.getPosition().y <= 18 * 27 + 13;
}

void CGhost::ChooseNextTile() {

	set<DIRECTION> availableDirs = { DIRECTION::LEFT, DIRECTION::RIGHT, DIRECTION::UP, DIRECTION::DOWN };

	//remove 180 degree direction
	switch (mDir) {
	case DIRECTION::LEFT:
		availableDirs.erase(DIRECTION::RIGHT);
		break;
	case DIRECTION::RIGHT:
		availableDirs.erase(DIRECTION::LEFT);
		break;
	case DIRECTION::UP:
		availableDirs.erase(DIRECTION::DOWN);
		break;
	case DIRECTION::DOWN:
		availableDirs.erase(DIRECTION::UP);
		break;
	}

	set<DIRECTION> temp = availableDirs;
	for (auto i : temp) {
		if (TileBlocked(i)) {
			availableDirs.erase(i);
		}
	}

	DIRECTION shortestDir;
	float currShortestDistance = 10000000;
	for (const auto &i : availableDirs) {
		float distance = CalculateDistance(i);
		if (distance < currShortestDistance) {
			currShortestDistance = distance;
			shortestDir = i;
		}
		else if (distance == currShortestDistance) {
			//priorities
			if (i == DIRECTION::UP || shortestDir == DIRECTION::UP) shortestDir = DIRECTION::UP;
			else if (i == DIRECTION::LEFT || shortestDir == DIRECTION::LEFT) shortestDir = DIRECTION::LEFT;
			else if (i == DIRECTION::DOWN || shortestDir == DIRECTION::DOWN) shortestDir = DIRECTION::DOWN;
			else shortestDir = DIRECTION::RIGHT;
		}
	}

	if (SpecialIntersection() && shortestDir == DIRECTION::UP) {
		cout << "Special intersection!" << endl;
		return;
	}
	SwitchDirection(shortestDir);
}

bool CGhost::SpecialIntersection() {
	int i = static_cast<int>((mY - 13) / 27);
	int j = static_cast<int>((mX - 13) / 27);

	return (i == 14 && j == 12) || (i == 14 && j == 15) || (i == 26 && j == 12) || (i == 26 && j == 15);
	//14 and 12, 14 and 15
	//26, and 12, 26 and 15 
}

float CGhost::CalculateDistance(const DIRECTION& dir) {

	int i = static_cast<int>((mY - 13) / 27);
	int j = static_cast<int>((mX - 13) / 27);
	
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
	//cout << "calculating distance from : " << i << ", " << j << endl;
	//cout << "to target I, J : " << targetI << ", " << targetJ << endl;

	int y = abs(targetI - i);
	int x = abs(targetJ - j);

	float distance = sqrt(pow(y, 2) + pow(x, 2));
	//cout << "distance : " << distance << endl;

	return distance;
}

bool CGhost::TileBlocked(const DIRECTION& dir) {
	int i = static_cast<int>((mY - 13) / 27);
	int j = static_cast<int>((mX - 13) / 27);

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

	if (mMapSketch[i][j] == '#') {
		return true;
	}
	else if (mMapSketch[i][j] == '@' && !IsInGhostBox() && mState != BEHAVIOUR::EATEN) return true;

	return false;
}

const void CGhost::ReverseDir(){
	switch (mDir) {
	case DIRECTION::UP:
		mDir = DIRECTION::DOWN;
		break;
	case DIRECTION::DOWN:
		mDir = DIRECTION::UP;
		break;
	case DIRECTION::RIGHT:
		mDir = DIRECTION::LEFT;
		break;
	case DIRECTION::LEFT:
		mDir = DIRECTION::RIGHT;
		break;

	}
}

void CGhost::SwitchDirection(const DIRECTION& dir) {
	//cout << "switched!" << "\n\n\n\n\n\n\n";
	mDir = dir;

	switch (mDir) {
	case DIRECTION::UP:
		mMovementX = 0.f;
		mMovementY = -mMovementSpeed;
		break;
	case DIRECTION::DOWN:
		mMovementX = 0.f;
		mMovementY = mMovementSpeed;
		break;
	case DIRECTION::LEFT:
		mMovementX = -mMovementSpeed;
		mMovementY = 0.f;
		break;
	case DIRECTION::RIGHT:
		mMovementX = mMovementSpeed;
		mMovementY = 0.f;
		break;
	}

	UpdateDirTexture();
}

bool CGhost::BlinkFrightenedTextures() {
	mBlinkTimer++;
	if (mBlinkTimer <= 50) return true;
	else if (mBlinkTimer <= 100) return false;
	else mBlinkTimer = 0;
}

void CGhost::UpdateMove(){
	mGhost.move(mMovementX, mMovementY);
	mX = mGhost.getPosition().x;
	mY = mGhost.getPosition().y;
}

void CGhost::Update() {
	UpdateMove();
	UpdateDirTexture();
}

void CGhost::Render(sf::RenderTarget* target){
	target->draw(mGhost);
}
