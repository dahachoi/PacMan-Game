#include "CPacMan.h"

using namespace std;

CPacMan::CPacMan()
{
	InitVariables();
	InitPacMan();
}

void CPacMan::InitVariables()
{
	mX = 14 * 27; //14 * 27
	mY = 715; //26.5 * 27

	mMovementSpeed = 1.f;
	mMovementX = 0.f;
	mMovementY = 0.f;

	mCurrDir = DIRECTION::NONE;
	mQuedDir = DIRECTION::NONE;
}

void CPacMan::InitPacMan()
{
	mPacMan.setRadius(22);
	mPacMan.setFillColor(sf::Color::Yellow);
	mPacMan.setOrigin(mPacMan.getGlobalBounds().width / 2, mPacMan.getGlobalBounds().height / 2);
	mPacMan.setPosition(mX, mY);
}

void CPacMan::SetPosition(const float& x, const float& y) {
	mX = x;
	mY = y;

	mPacMan.setPosition(mX, mY);
}

const sf::CircleShape &CPacMan::GetShape() const {
	return mPacMan;
}

const sf::Vector2f CPacMan::GetGridCoordinate() const{
	float x = mPacMan.getPosition().x - 13;
	float y = mPacMan.getPosition().y - 13;

	return sf::Vector2f(x, y);
}

const bool CPacMan::IsStopped() const {
	return mMovementX == 0.f && mMovementY == 0.f;
}

const DIRECTION& CPacMan::GetCurrDir() const {
	return mCurrDir;
}

const DIRECTION& CPacMan::GetQuedDir() const {
	return mQuedDir;
}
//Movement
void CPacMan::SwitchDirection() {
	mCurrDir = mQuedDir;

	//UpdateDirectionTexture();

	switch (mCurrDir) {
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
}

const void CPacMan::StopPacMan() {
	mMovementX = 0.f;
	mMovementY = 0.f;
}

void CPacMan::UpdateInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		mQuedDir = DIRECTION::UP;
		if (mCurrDir == DIRECTION::DOWN) SwitchDirection();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		mQuedDir = DIRECTION::LEFT;
		if (mCurrDir == DIRECTION::RIGHT) SwitchDirection();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		mQuedDir = DIRECTION::DOWN;
		if (mCurrDir == DIRECTION::UP) SwitchDirection();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		mQuedDir = DIRECTION::RIGHT;
		if (mCurrDir == DIRECTION::LEFT) SwitchDirection();
	}
}

void CPacMan::UpdateMove() {
	mPacMan.move(mMovementX, mMovementY);
}

//Public Update & Render
void CPacMan::Update() {
	UpdateInput();
	UpdateMove();
}

void CPacMan::Render(sf::RenderTarget* target) {
	target->draw(mPacMan);
}