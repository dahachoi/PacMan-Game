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
	mWindow->setFramerateLimit(240);
}

//Update
void CGame::UpdatePacMan() {
	iPacMan.Update();
}

void CGame::UpdateCollision() {
	sf::Vector2f pacManPos = iPacMan.GetGridCoordinate();
	float pacManX = pacManPos.x;
	float pacManY = pacManPos.y;

	// Collision with wall
	if (fmod(pacManX, 27) == 0.0 && fmod(pacManY, 27) == 0.0 || iPacMan.IsStopped()) {
		if (!iMap.UpdateCollision(pacManX, pacManY, iPacMan.GetQuedDir())) {
			iPacMan.SwitchDirection();
		}
		else if (iMap.UpdateCollision(pacManX, pacManY, iPacMan.GetCurrDir())) {
			iPacMan.StopPacMan();
		}
	}
}

//Render

void CGame::RenderMap() {
	iMap.Render(mWindow);
	iPacMan.Render(mWindow);
}
void CGame::Update() {
	PollEvents();
	if (!mEndGame) {
		UpdatePacMan();
		UpdateCollision();
		//Update Game objects
	}
}

void CGame::Render() {
	mWindow->clear();
	//render objects
	RenderMap();

	mWindow->display();
}