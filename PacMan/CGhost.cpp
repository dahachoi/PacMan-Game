#include "CGhost.h"

using namespace std;

void CGhost::FrightenedState()
{
}

void CGhost::EatenState()
{
}

void CGhost::SetPosition(const float& x, const float& y) {
	mX = x;
	mY = y;

	mGhost.setPosition(mX, mY);
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
}
const void CGhost::SwitchChase(){
	mState = BEHAVIOUR::CHASE;
}
const void CGhost::SwitchFrightened() {
	mState = BEHAVIOUR::FRIGHTENED;
}
const void CGhost::SwitchEaten() {
	mState = BEHAVIOUR::EATEN;
}

const BEHAVIOUR& CGhost::GetBehaviour() const{
	return mState;
}

void CGhost::ChooseNextTile() {
	set<DIRECTION> availableDirs = { DIRECTION::LEFT, DIRECTION::RIGHT, DIRECTION::UP, DIRECTION::DOWN };

	//remove 180 degree direction
	switch (mDir) {
	case DIRECTION::LEFT:
		//cout << "erased right as opposite" << endl;
		availableDirs.erase(DIRECTION::RIGHT);
		break;
	case DIRECTION::RIGHT:
		//cout << "erased left as opposite" << endl;
		availableDirs.erase(DIRECTION::LEFT);
		break;
	case DIRECTION::UP:
		//cout << "erased down as opposite" << endl;
		availableDirs.erase(DIRECTION::DOWN);
		break;
	case DIRECTION::DOWN:
		//cout << "erased up as opposite" << endl;
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
	//cout << "checking : ";
	//switch (dir) {
	//case DIRECTION::LEFT:
	//	cout << "LEFT" << endl;
	//	break;
	//case DIRECTION::RIGHT:
	//	cout << "RIGHT" << endl;
	//	break;
	//case DIRECTION::UP:
	//	cout << "UP" << endl;
	//	break;
	//case DIRECTION::DOWN:
	//	cout << "DOWN" << endl;
	//	break;
	//}

	//cout << "mX, mY : " << mX - 13 << ", " << mY - 13<< endl;

	int i = static_cast<int>((mY - 13) / 27);
	int j = static_cast<int>((mX - 13) / 27);
	//cout << "current: i, j :" << i << ", " << j << endl;

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
	//cout << "checking i, j :" << i << ", " << j << endl;
	if (mMapSketch[i][j] == '#') {
		//cout << "wall!" << endl<<endl;
		return true;
	}
	//cout << "no wall!" << endl << endl;
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

void CGhost::UpdateMove(){
	mGhost.move(mMovementX, mMovementY);
	mX = mGhost.getPosition().x;
	mY = mGhost.getPosition().y;
}

void CGhost::Update() {
	UpdateMove();
}

void CGhost::Render(sf::RenderTarget* target){
	target->draw(mGhost);
}
