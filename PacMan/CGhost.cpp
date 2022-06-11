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

void CGhost::UpdateTarget(const float& x, const float&y) {
	targetX = x;
	targetY = y;
}

void CGhost::ChooseNextTile() {
	set<DIRECTION> availableDirs = { DIRECTION::LEFT, DIRECTION::RIGHT, DIRECTION::UP, DIRECTION::DOWN };

	//remove 180 degree direction
	switch (mDir) {
	case DIRECTION::LEFT:
		cout << "erased right as opposite" << endl;
		availableDirs.erase(DIRECTION::RIGHT);
		break;
	case DIRECTION::RIGHT:
		cout << "erased left as opposite" << endl;
		availableDirs.erase(DIRECTION::LEFT);
		break;
	case DIRECTION::UP:
		cout << "erased down as opposite" << endl;
		availableDirs.erase(DIRECTION::DOWN);
		break;
	case DIRECTION::DOWN:
		cout << "erased up as opposite" << endl;
		availableDirs.erase(DIRECTION::UP);
		break;
	}

	set<DIRECTION> temp = availableDirs;
	for (auto i : temp) {
		if (TileBlocked(i)) {
			availableDirs.erase(i);
		}
	}

	cout << "available Directions : \n";
	for (auto i : availableDirs) {
		switch (i) {
		case DIRECTION::LEFT:
			cout << "LEFT" << endl;
			break;
		case DIRECTION::RIGHT:
			cout << "RIGHT" << endl;
			break;
		case DIRECTION::UP:
			cout << "UP" << endl;
			break;
		case DIRECTION::DOWN:
			cout << "DOWN" << endl;
			break;
		}
	}

	cout << endl;
	

}

bool CGhost::TileBlocked(const DIRECTION& dir) {
	cout << "checking : ";
	switch (dir) {
	case DIRECTION::LEFT:
		cout << "LEFT" << endl;
		break;
	case DIRECTION::RIGHT:
		cout << "RIGHT" << endl;
		break;
	case DIRECTION::UP:
		cout << "UP" << endl;
		break;
	case DIRECTION::DOWN:
		cout << "DOWN" << endl;
		break;
	}

	cout << "mX, mY : " << mX - 13 << ", " << mY - 13<< endl;

	int i = static_cast<int>((mY - 13) / 27);
	int j = static_cast<int>((mX - 13) / 27);
	cout << "current: i, j :" << i << ", " << j << endl;

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
	cout << "checking i, j :" << i << ", " << j << endl;
	if (mMapSketch[i][j] == '#') {
		cout << "wall!" << endl<<endl;
		return true;
	}
	cout << "no wall!" << endl << endl;
	return false;
}

void CGhost::SwitchDirection(const DIRECTION& dir) {
	cout << "switched!" << "\n\n\n\n\n\n\n";
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
