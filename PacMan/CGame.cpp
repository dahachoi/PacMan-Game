#include "CGame.h"

using namespace std;

CGame::CGame() {
	InitVariables();
	InitWindow();
}

CGame::~CGame() {
	delete mWindow;
}

void CGame::PollEvents() {
	while (mWindow->pollEvent(mEv)) {
		switch (mEv.type) {
		case sf::Event::Closed:
			mWindow->close();
			break;
		case sf::Event::KeyPressed:
			if (mEv.key.code == sf::Keyboard::Escape)
				mWindow->close();
			break;
		}
	}
}

const bool CGame::Running() const {
	return mWindow->isOpen();
}

void CGame::InitVariables() {
	mEndGame = false;
}

void CGame::InitWindow() {
	mVideoMode = sf::VideoMode(WIDTH, HEIGHT);
	mWindow = new sf::RenderWindow(mVideoMode, "PacMan", sf::Style::Close | sf::Style::Titlebar);
	mWindow->setFramerateLimit(144);
}

void CGame::Update() {
	PollEvents();
	if (!mEndGame) {
		//Update Game objects
	}
}

void CGame::Render() {
	mWindow->clear();
	//render objects

	mWindow->display();
}