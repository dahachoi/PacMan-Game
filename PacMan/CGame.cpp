#include "CGame.h"

using namespace std;

CGame::CGame() 
	: mMaxScore(2600)
{
	InitVariables();
	InitWindow();
	InitGhosts();
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

void CGame::InitGhosts() {
	mGhostContainer.push_back(new CRedGhost);
	mGhostContainer.push_back(new CPinkGhost);
}

void CGame::InitWindow() {
	mVideoMode = sf::VideoMode(WIDTH, HEIGHT);
	mWindow = new sf::RenderWindow(mVideoMode, "PacMan", sf::Style::Close | sf::Style::Titlebar);
	mWindow->setFramerateLimit(240);
}

//Update
void CGame::UpdatePacMan() {
	iPacMan.Update();
	UpdatePacManCollision();
}

void CGame::UpdateGhosts() {
	
	for (auto i : mGhostContainer){
		UpdateGhostBehaviour(i);
		i->Update();
		UpdateGhostCollision(i);
	}
	
	//iRedGhost.Update();

	
}

void CGame::UpdatePacManCollision() {
	sf::CircleShape mPacMan = iPacMan.GetShape();
	sf::Vector2f pacManPos = iPacMan.GetGridCoordinate();
	float pacManX = pacManPos.x;
	float pacManY = pacManPos.y;
	const float pacManWidth = 44.f;

	//side of screen
	if (pacManX <= 0) {
	/*	if (pacManX == 0) {
			iMap.UpdateCoinCollision(pacManX, pacManY);
		}*/

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
	//cout << "pacManX, pacManY : " << pacManX << ", " << pacManY << endl;
	if (fmod(pacManX, 27) == 0.0 && fmod(pacManY, 27) == 0.0 || iPacMan.IsStopped()) {
		//cout << "pacman is on grid!" << endl;
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

			if (gainPoints == 50) {
				for (auto i : mGhostContainer) {
					if (i->GetBehaviour() == BEHAVIOUR::FRIGHTENED) {
						mFrightenedTime += mDeltaTime;
					}
					else mLastBhvr = i->GetBehaviour();

					mFrightenedClock.restart();
					i->SwitchFrightened();
					i->ReverseDir();
					cout << "ENTERED FRIGHTENED ----------------------------------------------------------------------------" << endl;
				}

			}

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
	for (auto i : mGhostContainer) {
		i->UpdateTarget(pacManX, pacManY);
	}

	//iRedGhost.UpdateTarget(pacManX, pacManY);
	//iCyanGhost.Update.......
	//....
}

void CGame::UpdateGhostCollision(CGhost *ghost) {
	sf::Sprite mGhost = ghost->GetShape();
	sf::Vector2f mGhostPos = ghost->GetGridCoordinate();
	float ghostX = mGhostPos.x;
	float ghostY = mGhostPos.y;
	float ghostWidth = 44.f;
	
	//side of screen
	if (ghostX <= 0) {
		/*	if (pacManX == 0) {
				iMap.UpdateCoinCollision(pacManX, pacManY);
			}*/

		if (ghostX == -ghostWidth * 2 && ghostY == 17.f * 27.f) {
			ghost->SetPosition(float(WIDTH) + ghostWidth + 13, ghostY + 13.f);
		}
		return;
	}
	else if (ghostX >= WIDTH) {
		if (ghostX == WIDTH + ghostWidth && ghostY == 17.f * 27.f) {
			ghost->SetPosition((13 - ghostWidth) * 2, ghostY + 13.f);
		}
		return;
	}
	//cout << "ghost : " << ghostX << ", " << ghostY << endl;

	if (fmod(ghostX, 27) == 0.0 && fmod(ghostY, 27) == 0.0) {
		ghost->ChooseNextTile();
		//iCyanGhost.chooseNextTile();
		//iPinkGhost.chooseNextTile();
		//iYellowGhost.chooseNextTile();
	}
}

void CGame::UpdateGhostBehaviour(CGhost *ghost) {
	//cout << "Time : " << mTime.asSeconds() << endl;
	BEHAVIOUR currBhvr = ghost->GetBehaviour();
	
	if (currBhvr == BEHAVIOUR::EATEN) {
		sf::Vector2f pos = ghost->GetGridCoordinate();
		if (pos.x == 13 * 27 && pos.y == 17 * 27) ghost->SwitchManualBhvr(mLastBhvr);
		return;
	}

	if (currBhvr == BEHAVIOUR::FRIGHTENED) {
		mDeltaTime = mFrightenedClock.getElapsedTime();
		if (mDeltaTime.asSeconds() >= 8) {
			mFrightenedTime += mDeltaTime;
			ghost->SwitchManualBhvr(mLastBhvr);
		}
		return;
	}
	
	mTime = mClock.getElapsedTime() - mFrightenedTime;
	cout << "mTime : " << mTime.asSeconds() << endl;

	bool switched = false;

	//Switch From Scatter to Chase
	if (currBhvr == BEHAVIOUR::SCATTER){
		if (mTime.asSeconds() >= 7 && mChaseWave <= 2) {
			SwitchAllGhostBhvr(BEHAVIOUR::CHASE);
			//ghost->SwitchChase();
			switched = true;
			//and the others
		}
		else if (mTime.asSeconds() >= 5 && mChaseWave > 2 && mChaseWave <= 4) {
			SwitchAllGhostBhvr(BEHAVIOUR::CHASE);
			//ghost->SwitchChase();
			switched = true;
		}
	}
	
	//Switch from Chase to Scatter
	if (currBhvr == BEHAVIOUR::CHASE && mChaseWave != 4) {
		if (mTime.asSeconds() >= 20) {
			SwitchAllGhostBhvr(BEHAVIOUR::SCATTER);
			ghost->SwitchScatter();
			mChaseWave++;
			switched = true;
		}
	}

	if (switched) {
		ghost->ReverseDir();
		mClock.restart();
		mFrightenedTime = sf::milliseconds(0);
	}
	
}

void CGame::SwitchAllGhostBhvr(const BEHAVIOUR& bhvr) {
	for (auto i : mGhostContainer)
		i->SwitchManualBhvr(bhvr);
}

void CGame::UpdateCollision(CGhost *ghost) {
	sf::CircleShape mPacMan = iPacMan.GetShape();
	sf::Sprite mGhost = ghost->GetShape();

	bool collision = false;
	if (mPacMan.getPosition().x == mGhost.getPosition().x) {
		if (abs(mPacMan.getPosition().y - mGhost.getPosition().y) <= 27) collision = true;
	}
	else if (mPacMan.getPosition().y == mGhost.getPosition().y) {
		if (abs(mPacMan.getPosition().x - mGhost.getPosition().x) <= 27) collision = true;

	}

	if (collision) {
		if (ghost->GetBehaviour() == BEHAVIOUR::CHASE || ghost->GetBehaviour() == BEHAVIOUR::SCATTER) mEndGame = true;
		else {
			ghost->SwitchEaten();

			sf::Clock coolDown;
			sf::Time coolDownTime;
			mScore += 200;
		}
	}


	//UpdatePacManCollision();
	//UpdateGhostCollision();
}

//Render

void CGame::RenderGhosts() {
	for (auto i : mGhostContainer) {
		i->Render(mWindow);
	}
}

void CGame::RenderMap() {
	iMap.Render(mWindow);
	iPacMan.Render(mWindow);
}
void CGame::Update() {
	PollEvents();
	if (!mEndGame) {
		UpdateGhosts();
		UpdatePacMan();

		for (auto i : mGhostContainer) {
			UpdateCollision(i);
		}
		
		//UpdateCollision();
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