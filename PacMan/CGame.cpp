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

void CGame::UpdateGhosts() {
	iRedGhost.Update();
}

void CGame::UpdatePacManCollision() {
	sf::CircleShape mPacMan = iPacMan.GetShape();
	sf::Vector2f pacManPos = iPacMan.GetGridCoordinate();
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
		UpdateGhostTarget(pacManX, pacManY);
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

void CGame::UpdateGhostTarget(const float& pacManX, const float& pacManY) {
	iRedGhost.UpdateTarget(pacManX, pacManY);
	//iCyanGhost.Update.......
	//....
}

void CGame::UpdateGhostCollision() {
	sf::Sprite mGhost = iRedGhost.GetShape();
	sf::Vector2f mGhostPos = iRedGhost.GetGridCoordinate();
	float ghostX = mGhostPos.x;
	float ghostY = mGhostPos.y;

	//cout << "ghost : " << ghostX << ", " << ghostY << endl;

	if (fmod(ghostX, 27) == 0.0 && fmod(ghostY, 27) == 0.0) {
		if (iMap.UpdateWallCollision(ghostX, ghostY, iRedGhost.GetDir())) {
			DIRECTION newDir;
			do {
				int randDir = rand() % 4;
				switch (randDir) {
				case 0:
					newDir = DIRECTION::LEFT;
					break;
				case 1:
					newDir = DIRECTION::RIGHT;
					break;
				case 2:
					newDir = DIRECTION::UP;
					break;
				case 3:
					newDir = DIRECTION::DOWN;
					break;
				}

			} while (iMap.UpdateWallCollision(ghostX, ghostY, newDir));
			iRedGhost.SwitchDirection(newDir);
		}

		//iRedGhost.SetPosition(ghostX, ghostY);
		iRedGhost.ChooseNextTile();
		//iCyanGhost.chooseNextTile();
		//iPinkGhost.chooseNextTile();
		//iYellowGhost.chooseNextTile();
	}
}

void CGame::UpdateCollision() {
	UpdatePacManCollision();
	UpdateGhostCollision();
}

//Render

void CGame::RenderGhosts() {
	iRedGhost.Render(mWindow);
}

void CGame::RenderMap() {
	iMap.Render(mWindow);
	iPacMan.Render(mWindow);
}
void CGame::Update() {
	PollEvents();
	if (!mEndGame) {
		UpdatePacMan();
		UpdateGhosts();
		UpdateCollision();
		//Update Game objects
	}
}

void CGame::Render() {
	mWindow->clear();
	//render objects
	RenderMap();
	RenderGhosts();
	//RenderTestGhost();

	mWindow->display();
}