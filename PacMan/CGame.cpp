#include "CGame.h"

using namespace std;

CGame::CGame() 
	: mMaxScore(2600)
{
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
	mScore = 0;
	mGainPoints = 10;
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
	sf::CircleShape mPacMan = iPacMan.GetShape();
	float pacManX = pacManPos.x;
	float pacManY = pacManPos.y;
	const float pacManWidth = 44.f;

	//side of screen
	if (pacManX <= 0) {
		if (pacManX == 0) {
			iMap.UpdateCoinCollision(pacManX, pacManY);
		}

		if (pacManX == -pacManWidth * 2 && pacManY == 17.f * 27.f) {
			iPacMan.SetPosition(float(WIDTH) + pacManWidth + 13, pacManY + 13.f);
		}
		return;
	}
	else if (pacManX >= WIDTH) {
		if (pacManX == WIDTH + pacManWidth && pacManY == 17.f * 27.f) {
			iPacMan.SetPosition((13 - pacManWidth) * 2, pacManY + 13.f);
		}
		return;
	}

	// Collision with wall
	if (fmod(pacManX, 27) == 0.0 && fmod(pacManY, 27) == 0.0 || iPacMan.IsStopped()) {
		if (!iMap.UpdateWallCollision(pacManX, pacManY, iPacMan.GetQuedDir())) {
			iPacMan.SwitchDirection();
		}
		else if (iMap.UpdateWallCollision(pacManX, pacManY, iPacMan.GetCurrDir())) {
			iPacMan.StopPacMan();
		}

		if (int gainPoints = iMap.UpdateCoinCollision(pacManX, pacManY)) {
			//cout << "Collision! gained : " << gainPoints << endl;
			mScore += gainPoints;
			cout << "mScore : " << mScore << endl;
			//cout << "mScore : " << mScore << endl;
			if (mScore == mMaxScore) {
				cout << "end game" << endl;
				//mEndGame = true;
			}
		}
	}
	//cout << endl;
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